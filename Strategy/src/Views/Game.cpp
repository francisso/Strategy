/*
 * Game.cpp
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#include "Game.h"
#include "../Constants.h"
#include <string>
#include <iostream>

Game::Game(Drawable** texture) : Game(texture, new GameField()) {}

Game::Game(Drawable** texture, GameField* field) : field(field), texture(texture) {
	x = 0;
	y = 0;
}

void Game::Draw(std::function<void (Drawable*, CoordinateType X0, CoordinateType Y0)> f) const {
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++) {
		texture[field->grid[i][k].textureType]->SetX(static_cast<float>(CELL_X_PIXELS*i));
		texture[field->grid[i][k].textureType]->SetY(static_cast<float>(CELL_Y_PIXELS*k));
		f(texture[field->grid[i][k].textureType], -x, -y);
	}
	for (int i = 0;	i < CELL_X_NUMBER; i++)
	for (int k = 0;	k < CELL_Y_NUMBER; k++)
				f(field->grid[i][k].object, -x, -y);
	f(field->selection, -x, -y);
	this->View::Draw(f);
}

inline int Sign(bool isPositive) {
	return isPositive ? 1 : -1;
}
void Game::MotionMap(Time t)
{
	int X = 0, Y = 0;
	SDL_GetMouseState(&X, &Y);
	// TODO убрать константу 5
	if (X < 5) {
		if (x >= SpeedMap*t)
			x -= SpeedMap*t;
		else x = 0;
	}
	if (Y < 5) {
		if (y >= SpeedMap*t)
			y -= SpeedMap*t;
		else y = 0;
	}
	if (X > X_SIZE_WINDOW - 5) {
		if (x < CELL_X_NUMBER*CELL_X_PIXELS - X_SIZE_WINDOW - SpeedMap*t)
			x += SpeedMap*t;
		else x = CELL_X_NUMBER*CELL_X_PIXELS - X_SIZE_WINDOW;
	}
	if (Y > Y_SIZE_WINDOW - 5) {
		if (y < CELL_Y_NUMBER*CELL_Y_PIXELS - Y_SIZE_WINDOW - SpeedMap*t)
			y += SpeedMap*t;
		else y = CELL_Y_NUMBER*CELL_Y_PIXELS - Y_SIZE_WINDOW;
	}
}
void Game::Update(Time t) {
	MotionMap(t);
	Action* action;
	Unit* unit;
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++) {
		//Пока что осуществляем действия только для юнитов
		if (field->grid[i][k].objectType != CellType::UNIT)
			continue;
		unit=dynamic_cast<Unit*>(field->grid[i][k].object);
		action = unit->GetAction();
		//std::cout<<"ActionType is "<<ActionOut(action)<<std::endl;
		if (action->actionType==Action::STAY){
			unit->SetVirtualX(unit->GetX());
			unit->SetVirtualY(unit->GetY());
			unit->NextAction();
			//std::cout<<unit->GetVirtualX()<<"=GetVirtualX()=GetX()="<<unit->GetX()<<std::endl;
		}
		if (action->actionType==Action::MOVE_VERTICAL){
			//auto x = unit->GetX();
			auto y = unit->GetY();
			if(y==CELL_Y_PIXELS*k){
				if(field->grid[i][k+Sign(action->IsPositive)].objectType==CellType::NOTHING){
					field->grid[i][k+Sign(action->IsPositive)].objectType=CellType::OCCUPIED;
					unit->SetY(y+t*unit->GetMaxSpeed()*static_cast<float>(Sign(action->IsPositive)));
				}
				else continue;
			} else {
				if((y+t*unit->GetMaxSpeed())>=CELL_Y_PIXELS*(k+1) || (y-t*unit->GetMaxSpeed())<=CELL_Y_PIXELS*(k-1)){
					int y_next = k+Sign(action->IsPositive);
					field->grid[i][y_next].objectType = CellType::UNIT;
					field->grid[i][y_next].object = unit;
					field->grid[i][k].objectType = CellType::NOTHING;
					field->grid[i][k].object = nullptr;
					unit->SetY(static_cast<float>(CELL_Y_PIXELS*y_next));
					unit->NextAction();
					//std::cout<<"ActionType is "<<ActionOut(unit->GetAction())<<std::endl;
				} else {
					unit->SetY(y+t*unit->GetMaxSpeed()*static_cast<float>(Sign(action->IsPositive)));
				}
			}
		}
		if (action->actionType==Action::MOVE_HORIZONTAL){
			auto x=unit->GetX();
			if(x==CELL_X_PIXELS){
				if(field->grid[i+Sign(action->IsPositive)][k].objectType==CellType::NOTHING){
					field->grid[i+Sign(action->IsPositive)][k].objectType=CellType::OCCUPIED;
					unit->SetX(x+t*unit->GetMaxSpeed()*static_cast<float>(Sign(action->IsPositive)));
				}
				else continue;
			} else {
				if((x+t*unit->GetMaxSpeed())>=CELL_Y_PIXELS*(i+1) || (x-t*unit->GetMaxSpeed())<=CELL_Y_PIXELS*(i-1)){
					int x_next = i+Sign(action->IsPositive);
					field->grid[x_next][k].objectType = CellType::UNIT;
					field->grid[x_next][k].object = unit;
					field->grid[i][k].objectType = CellType::NOTHING;
					field->grid[i][k].object = nullptr;
					unit->SetX(static_cast<float>(x_next*CELL_X_PIXELS));
					unit->NextAction();
				} else {
					unit->SetX(x+t*unit->GetMaxSpeed()*static_cast<float>(Sign(action->IsPositive)));
				}
			}
		}
		//TODO удалить это
		/*if (action->actionType == Action::MOVE) {
			auto move = static_cast<ActionMove*>(action);
			auto unit = reinterpret_cast<Unit*>(action->who);
			auto x = unit->GetX();
			auto y = unit->GetY();
			//если юнит целиком в одной клетке
			if (x == CELL_X_PIXELS*i && y == CELL_Y_PIXELS*k) {
				//если юнит движется вдоль осей координат
				if (move->x_speed*move->y_speed == 0) {
					//TODO check ranges and refactor
					if(field->grid[i+sign(move->x_speed)][k+sign(move->y_speed)].objectType == CellType::NOTHING)
						field->grid[i+sign(move->x_speed)][k+sign(move->y_speed)].objectType = CellType::OCCUPIED;
					else continue;
				}
				}
			else {
				//проверка, что юнит перешел в следующую клетку
				if (x > CELL_X_PIXELS*(i+1) || y > CELL_Y_PIXELS*(k+1) ||
						x < CELL_X_PIXELS*(i-1) || y < CELL_Y_PIXELS*(k-1)) {
					int x_next = i +sign(move->x_speed);
					int y_next = k +sign(move->y_speed);
					field->grid[x_next][y_next].objectType = CellType::UNIT;
					field->grid[x_next][y_next].object = unit;
					field->grid[i][k].objectType = CellType::NOTHING;
					field->grid[i][k].object = nullptr;
					//Just an example of action
					auto temp = move->y_speed;
					move->y_speed = move->x_speed*-1.0f;
					move->x_speed = temp;
				}
			}
			unit->SetX(x+t*move->x_speed);
			unit->SetY(y+t*move->y_speed);
		}*/
	}
}

void Game::AddUnitAtCell(Unit* unit, int cell_x, int cell_y) {
	if (cell_x < 0 || cell_y < 0 || cell_x >= CELL_X_NUMBER || cell_y >= CELL_Y_NUMBER)
		return;
	auto cell = &this->field->grid[cell_x][cell_y];
	if (cell->objectType == CellType::NOTHING) {
		cell->objectType = CellType::UNIT;
		cell->object = unit;
	}
	std::cout<<"GetX()t="<<unit->GetX()<<" ;GetY()="<<unit->GetY()<<" ;GetVirtualX()="<<unit->GetVirtualX()<<" ;GetVirtualY()="<<unit->GetVirtualY()<<std::endl;
}


void Game::OnEvent(SDL_Event* event) {
	switch(event->type)
	{
	case SDL_MOUSEMOTION:
	{
		int X = static_cast<int>(x);
		int Y = static_cast<int>(y);
		int i = (X + event->motion.x) / CELL_X_PIXELS;
		int j = (Y + event->motion.y) / CELL_Y_PIXELS;
		field->selection->SetX(static_cast<float>(i*CELL_X_PIXELS));
		field->selection->SetY(static_cast<float>(j*CELL_Y_PIXELS));
	}
	}
}

std::string Game::ActionOut(Action* action){
	std::string s;
	if(action->actionType==Action::STAY)
		s="STAY";
	if(action->actionType==Action::MOVE_HORIZONTAL)
		s="MOVE_HORIZONTAL";
	if(action->actionType==Action::MOVE_VERTICAL)
		s="MOVE_VERTICAL";
	return s;
}

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

Game::Game(Drawable* background) : Game(background, new GameField()) {}

Game::Game(Drawable* background, GameField* field) : field(field), background(background) { }

void Game::Draw(std::function<void (Drawable*)> f) {
	f(background);
	for (int i = 0; i < CELL_X_NUMBER; i++)
		for (int k = 0; k < CELL_Y_NUMBER; k++)
			f(field->grid[i][k].object);
	f(field->selection);
	this->View::Draw(f);
}

inline int sign(bool IsPositive) {
	if (IsPositive)
		return 1;
	else
		return -1;
	//return 0;
}

void Game::Update(Time t) {
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
					if(field->grid[i][k+sign(action->IsPositive)].objectType==CellType::NOTHING){
						field->grid[i][k+sign(action->IsPositive)].objectType=CellType::OCCUPIED;
						unit->SetY(y+t*unit->GetMaxSpeed()*static_cast<float>(sign(action->IsPositive)));
					}
					else continue;
				} else {
					if((y+t*unit->GetMaxSpeed())>=CELL_Y_PIXELS*(k+1) || (y-t*unit->GetMaxSpeed())<=CELL_Y_PIXELS*(k-1)){
						int y_next = k+sign(action->IsPositive);
						field->grid[i][y_next].objectType = CellType::UNIT;
						field->grid[i][y_next].object = unit;
						field->grid[i][k].objectType = CellType::NOTHING;
						field->grid[i][k].object = nullptr;
						unit->SetY(static_cast<float>(CELL_Y_PIXELS*y_next));
						unit->NextAction();
						//std::cout<<"ActionType is "<<ActionOut(unit->GetAction())<<std::endl;
					} else {
						unit->SetY(y+t*unit->GetMaxSpeed()*static_cast<float>(sign(action->IsPositive)));
					}
				}
			}
			if (action->actionType==Action::MOVE_HORIZONTAL){
				auto x=unit->GetX();
				if(x==CELL_X_PIXELS){
					if(field->grid[i+sign(action->IsPositive)][k].objectType==CellType::NOTHING){
						field->grid[i+sign(action->IsPositive)][k].objectType=CellType::OCCUPIED;
						unit->SetX(x+t*unit->GetMaxSpeed()*static_cast<float>(sign(action->IsPositive)));
					}
					else continue;
				} else {
					if((x+t*unit->GetMaxSpeed())>=CELL_Y_PIXELS*(i+1) || (x-t*unit->GetMaxSpeed())<=CELL_Y_PIXELS*(i-1)){
						int x_next = i+sign(action->IsPositive);
						field->grid[x_next][k].objectType = CellType::UNIT;
						field->grid[x_next][k].object = unit;
						field->grid[i][k].objectType = CellType::NOTHING;
						field->grid[i][k].object = nullptr;
						unit->SetX(static_cast<float>(x_next*CELL_X_PIXELS));
						unit->NextAction();
					} else {
						unit->SetX(x+t*unit->GetMaxSpeed()*static_cast<float>(sign(action->IsPositive)));
					}
				}
			}


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
		int i = event->motion.x / CELL_X_PIXELS;
		int j = event->motion.y / CELL_Y_PIXELS;
		field->selection->SetX((float)i*CELL_X_PIXELS);
		field->selection->SetY((float)j*CELL_Y_PIXELS);
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

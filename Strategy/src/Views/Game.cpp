/*
 * Game.cpp
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#include "Game.h"
#include "../Constants.h"

Game::Game(Drawable* background) : Game(background, new GameField()) {};

Game::Game(Drawable* background, GameField* field) : field(field), background(background) { };

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::Draw(std::function<void (Drawable*)> f) {
	f(background);
	for (int i = 0; i < CELL_X_NUMBER; i++)
		for (int k = 0; k < CELL_Y_NUMBER; k++)
			f(field->grid[i][k].object);
	this->View::Draw(f);
}

inline int sign(float x) {
	if (x > 0)
		return 1;
	if (x < 0)
		return -1;
	return 0;
}

void Game::Update(Time t) {
	Action* action;
	for (int i = 0; i < CELL_X_NUMBER; i++)
		for (int k = 0; k < CELL_Y_NUMBER; k++) {
			//Пока что осуществляем действия только для юнитов
			if (field->grid[i][k].objectType != CellType::UNIT)
				continue;
			action = dynamic_cast<Unit*>(field->grid[i][k].object)->GetAction();
			if (action->actionType == Action::MOVE) {
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
			}
		}

}

void Game::AddUnitAtCell(Unit* unit, int cell_x, int cell_y) {
	//TODO check ranges
	auto cell = &this->field->grid[cell_x][cell_y];
	if (cell->objectType == CellType::NOTHING) {
		cell->objectType = CellType::UNIT;
		cell->object = unit;
	}
}

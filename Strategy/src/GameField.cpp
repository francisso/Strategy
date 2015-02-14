/*
 * GameField.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "GameField.h"

GameField::GameField() {
	// TODO Auto-generated constructor stub

}

GameField::~GameField() {
	// TODO Auto-generated destructor stub
}

bool GameField::AddGameObject(GameObject* addingObject, int type) {
	// TODO implement function
	return false;
}

GameObject* GameField::GetGameObjectAtCell(int x, int y) {
	// TODO implement function
	return nullptr;
}

GameObject* GameField::GetGameObjectAtCoorinates(CoordinateType x, CoordinateType y) {
	return GetGameObjectAtCell(x/CELL_X, y/CELL_Y);
}

/*
 * GameField.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

#include "../Constants.h"
#include "../Drawable/Draw.h"
#include "../Drawable/GameObject.h"

enum SelectionType {
	LEFT = 0,
	RIGHT = 1,
	HIGH = 2,
	LOW = 3
};
//Сетка для игровых объектов
struct GameField {
	Draw* selection[4];
	struct Cell {
		int textureType;
		int usedFor;
		GameObject* object;
	};
	Cell grid[CELL_X_NUMBER][CELL_Y_NUMBER];
};

#endif /* GAMEFIELD_H_ */

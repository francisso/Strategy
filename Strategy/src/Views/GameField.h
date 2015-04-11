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

//Сетка для игровых объектов
struct GameField {
	Draw* selection;
	struct Cell {
		int textureType;
		int objectType;
		GameObject* object;
	};
	Cell grid[CELL_X_NUMBER][CELL_Y_NUMBER];
};

#endif /* GAMEFIELD_H_ */

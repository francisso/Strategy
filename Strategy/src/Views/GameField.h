/*
 * GameField.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

#include "../Constants.h"
#include "../Drawable/GameObjects/PlayingObject.h"

//Сетка для игровых объектов
struct GameField {
	PlayingObject* selection;
	struct Cell {
		int textureType;
		int objectType;
		PlayingObject* object;
	};
	Cell grid[CELL_X_NUMBER][CELL_Y_NUMBER];
};

#endif /* GAMEFIELD_H_ */

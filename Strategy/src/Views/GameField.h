/*
 * GameField.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

#include "../Constants.h"
#include "../GameObject.h"


//Содержит все игровые объекты
struct GameField {
	struct CellType {
		int textureType;
		int objectType;
	};
	struct Cell {
		CellType type;
		GameObject* object;
	};
	Cell grid[CELL_X_NUMBER][CELL_Y_NUMBER];
};

#endif /* GAMEFIELD_H_ */

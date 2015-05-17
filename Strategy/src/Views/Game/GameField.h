/*
 * GameField.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

#include "../../Constants.h"
#include "../../Drawable/Draw.h"
#include "../../Drawable/GameObject.h"
#include "../../Types.h"
#include <queue>

enum SelectionType {
	LEFT = 0,
	RIGHT = 1,
	HIGH = 2,
	LOW = 3
};

struct Point {
	int x;
	int y;
};
//Сетка для игровых объектов
struct GameField {
	Draw* selection[4];
	struct Cell {
		int textureType;
		CellType usedFor;
		GameObject* object;
	};
	Cell grid[CELL_X_NUMBER][CELL_Y_NUMBER];

	void findPath(Point &startPoint, Point &finishPoint, std::queue<Point> &controlPoints);
	bool IsWalkable(int x, int y);
};

#endif /* GAMEFIELD_H_ */

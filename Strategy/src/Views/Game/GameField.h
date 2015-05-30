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
#include <iostream>

const int maxRadiusDefault=5;

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

	void FindPath_JPS(Point &startPoint, Point &finishPoint, std::queue<Point> &controlPoints, std::vector<Point> &forbiddenPoints);
	bool IsWalkable(int x, int y);
	bool IsInside(int x, int y);

	/**
	 * Ищет свободную ячейку в радиусе radius
	 * Возвращает Point свободной ячейки ближайших к заданной координатами x и y
	 * если не может найти свободную ячейку, возвращает -1 и -1 в полях Point
	 * если указан радиус по умолчанию или отрицательный, будет искать в радиусе maxRadiusDefault
	 */
	Point FindClosestFreeCell(int x, int y, int radius=0);
};

#endif /* GAMEFIELD_H_ */

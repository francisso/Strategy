/*
 * FieldBuilder.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: anton
 */

#include "FieldBuilder.h"



int FieldBuilder::Distance(Point a, Point b) {
	return abs(a.x-b.x)+abs(a.y-b.y);
}

int FieldBuilder::FindNearest(int x, int y, Point points[]) {
	int num = 0;
	int delta = INT32_MAX;
	int d = delta;
	Point point = {x,y};

	for (int i =0; i < ZONES_COUNT; i++) {
		d =Distance(point, points[i]);
		if (d < delta) {
			num=i;
			delta = d;
		}
	}
	return num;
}



GameField* FieldBuilder::CreateField() {
	srand(static_cast<unsigned int>(time(0)));
	SDL_Rect src = {0, 0, CELL_X_PIXELS, CELL_Y_PIXELS};
	GameField* field = new GameField();
	field->selection = new GameObject(src, "res/images/selection.bmp", 100);

	Point point;
	Point points[ZONES_COUNT];
	//Генерерием центры зон
	for (int i = 0; i < ZONES_COUNT; i++) {
		point.x = static_cast<int>(random() % (CELL_X_NUMBER));
		point.y = static_cast<int>(random() % (CELL_Y_NUMBER));
		points[i] = point;
		//проверяем, чтобы расстояние между центрами было не меньше минимального
		for (int k = 0; k < i; k++)
			if (Distance(point, points[k]) < MIN_DISTANCE) {
				i--;
				break;
			}
	}
	//Определяем тип текстуры в каждой клетке
	for (int x = 0; x < CELL_X_NUMBER; x++)
		for(int y = 0; y < CELL_Y_NUMBER; y++) {
			field->grid[x][y].textureType= FindNearest(x, y, points);
	}
	return field;
}



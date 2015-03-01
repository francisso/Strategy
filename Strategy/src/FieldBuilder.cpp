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
	srand(time(0));
	GameField* field = new GameField();
	Point point;
	Point points[ZONES_COUNT];
	//Генерерием центры зон
	for (int i = 0; i < ZONES_COUNT; i++) {
		point.x = random() % (CELL_X_NUMBER);
		point.y = random() % (CELL_Y_NUMBER);
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
			field->field[x][y].type.texstura= FindNearest(x, y, points);
	}
	return field;
}



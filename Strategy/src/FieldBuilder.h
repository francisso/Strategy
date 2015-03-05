/*
 * FieldBuilder.h
 *
 *  Created on: Mar 2, 2015
 *      Author: anton
 */

#ifndef FIELDBUILDER_H_
#define FIELDBUILDER_H_

#include "Views/GameField.h"

class FieldBuilder {
public:
	static GameField* CreateField();

private:
	static const int ZONES_COUNT= 6;
	//минимальное расстояние между зонами
	//если задать слишком большое, алгоритм может не завершиться
	static const int MIN_DISTANCE= 5;

	struct Point{ int x; int y;};

	//Расстояние между точкам (метод кварталов)
	static int Distance(Point a, Point b);

	//определяет индекс точки из points, ближайшей к (x,y)
	static int FindNearest(int x, int y, Point points[]);
};

#endif /* FIELDBUILDER_H_ */

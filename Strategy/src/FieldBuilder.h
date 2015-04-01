/*
 * FieldBuilder.h
 *
 *  Created on: Mar 2, 2015
 *      Author: anton
 */

#ifndef FIELDBUILDER_H_
#define FIELDBUILDER_H_

#include <fstream>
#include <string>

#include "Views/GameField.h"

using std::string;

class FieldBuilder {
public:
	static GameField* CreateField();
	//число областей с одной текстурой
	static const int ZONES_COUNT=10;
	//Количество текстур
	static const int TEXTURE_COUNT= 6;
	//минимальное расстояние между зонами
	//если задать слишком большое, алгоритм может не завершиться
	static const int MIN_DISTANCE= 5;
	//Путь, по которому лежит файл с картой.
	static const char* MAP_PATH;

private:
	struct Point{ int x; int y;};
	//Расстояние между точкам (метод кварталов)
	static int Distance(Point a, Point b);
	//определяет индекс точки из points, ближайшей к (x,y)
	//размер массива считается равным ZONES_COUNT
	static int FindNearest(int x, int y, Point points[]);
	//Инициализирует созданный field случайным образом.
	static void InitializeRandomField(GameField* field);
	//Инициализурет созданный field из файла по пути path
	static void LoadFromFile(GameField* field, const char* path);
};


#endif /* FIELDBUILDER_H_ */

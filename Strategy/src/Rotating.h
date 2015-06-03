/*
 * Angle.h
 *
 *  Created on: Apr 16, 2015
 *      Author: staslatgttt
 */

#ifndef ROTATING_H_
#define ROTATING_H_

#include <cmath>


//Константы для поворота объектов
const float tanPi1of8=0.414214f;
const float tanPi3of8=2.414214f;
const float sqrtOneSecond=0.707106f;

enum Direction{NORTH=0,NORTH_EAST=1,EAST=2,SOUTH_EAST=3,SOUTH=4,SOUTH_WEST=5,WEST=6,NORTH_WEST=7};

class Rotating{
	Direction angle;
public:
	Rotating(int ang);
	Rotating(Direction newDir);
	Rotating(Rotating* newAngle);
	~Rotating()=default;

	/**
	 * Функция чтобы узнать текущий угол
	 */
	Direction GetDirection();

	/**
	 * Установить значение угла
	 */
	void SetAngle(int ang);
	void SetAngle(Direction newDir);
	void SetAngle(Rotating* newAngle);

	/**
	 * Повернуть на заданный угол по часовой стрелке
	 * По умолчанию повернет в следующий сектор
	 */
	void TurnRight(int ang=1);

	/**
	 * Повернуть на заданный угол против часовой стрелки
	 * По умолчанию повернет в следующий сектор
	 */
	void TurnLeft(int ang=1);

	/**
	 * Вычисляет значение разности направлений
	 * Возвращает число, равное количеству углов PI/4, помещающихся между параметрами
	 */
	static int GetDifference(Direction dir1,Direction dir2);
	static int GetDifference(Direction dir, Rotating* rot);
	static int GetDifference(Rotating* rot1, Rotating* rot);
	static int GetDifference(Rotating* rot, Direction dir);

	/**
	 * Возвращает направление в зависимости от точки обзора
	 */
	static Direction Arctan(float delta_x,float delta_y);
	static Direction Arctan(int delta_x, int delta_y);

	/**
	 * Синус и косинус для получения модификатора скорости при движении по диагонали
	 */
	static float SpeedModifierX(Direction dir);
	static float SpeedModifierY(Direction dir);

	/**
	 * Добавка для обращения к следующей ячейке
	 */

	static int NextCellX(Direction dir);
	static int NextCellY(Direction dir);
};

#endif /* ROTATING_H_ */

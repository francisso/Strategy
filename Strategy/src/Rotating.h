/*
 * Angle.h
 *
 *  Created on: Apr 16, 2015
 *      Author: staslatgttt
 */

#ifndef ROTATING_H_
#define ROTATING_H_

#include <cmath>

const float tanPi1of8=0.414214f;
const float tanPi3of8=2.414214f;

enum Direction{UP=0,UP_RIGHT=1,RIGHT=2,DOWN_RIGHT=3,DOWN=4,DOWN_LEFT=5,LEFT=6,UP_LEFT=7};

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
	Direction GetAngle();

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
};

#endif /* ROTATING_H_ */

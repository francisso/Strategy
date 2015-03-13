/*
 * GameObject.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Drawable.h"
#include <iostream>

//Базовый класс для юнитов, зданий, и т.д.
class GameObject: public Drawable {
public:
	GameObject(SDL_Rect src, const char *name_file_image);
	virtual ~GameObject();
	//Обновляет состояние (положение) объекта на основе прошедшего времени
	virtual void Update(float time);
	//Реализация Drawable:
	virtual SDL_Surface* GetImage();
	virtual CoordinateType GetX();
	virtual CoordinateType GetY();
	virtual void SetX(CoordinateType x);
	virtual void SetY(CoordinateType y);
	virtual CoordinateType GetWidth();
	virtual CoordinateType GetHeight();
	// прямоугольник, куда нужно наложить картинку
	virtual SDL_Rect* GetSrcRect();
	// прямоугольник, который накладывается
	virtual SDL_Rect* GetDestRect();

	virtual bool ContainsCoordinates(float x, float y);

private:
	//Координаты на поле
	CoordinateType x;
	CoordinateType y;
	//Координаты верхнего левого угла прямоугольника,
	// который будет отрисован, на кратинке
	CoordinateType imageX;
	CoordinateType imageY;
	CoordinateType width;
	CoordinateType height;
	//Прямоугольники, дублирующие верхние переменные
	SDL_Rect* destRect;
	SDL_Rect* srcRect;
public:
	SDL_Surface* image;
};

#endif /* GAMEOBJECT_H_ */

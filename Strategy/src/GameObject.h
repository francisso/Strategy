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
	GameObject(SDL_Rect src, const char *name_file_image, Uint8 transparency =255 );
	virtual ~GameObject();
	//Обновляет состояние (положение) объекта на основе прошедшего времени
	virtual void Update(float time);
	//Реализация Drawable:
	virtual SDL_Surface* GetImage() const;
	virtual CoordinateType GetX() const;
	virtual CoordinateType GetY() const;
	virtual void SetX(CoordinateType x);
	virtual void SetY(CoordinateType y);
	virtual CoordinateType GetWidth() const;
	virtual CoordinateType GetHeight() const;
	virtual SDL_Rect* GetSrcRect() const;
	virtual SDL_Rect* GetDestRect() const;

	virtual bool ContainsCoordinates(float x, float y) const;

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
	//прямоугольник, куда рисуется изображение
	SDL_Rect* destRect;
	//определяет, какую часть исходного изображения рисовать
	SDL_Rect* srcRect;
public:
	SDL_Surface* image;
};

#endif /* GAMEOBJECT_H_ */

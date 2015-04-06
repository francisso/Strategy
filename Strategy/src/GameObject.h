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
	GameObject(SDL_Rect src, Uint8 r, Uint8 g, Uint8 b);
	virtual ~GameObject();
	//Обновляет состояние (положение) объекта на основе прошедшего времени
	virtual void Update(float time);
	//Реализация Drawable:
	virtual SDL_Surface* GetImage() const;
	virtual float GetX() const;
	virtual float GetY() const;
	virtual void SetX(float x);
	virtual void SetY(float y);
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual SDL_Rect* GetSrcRect() const;
	virtual SDL_Rect* GetDestRect() const;
	virtual bool ContainsCoordinates(float x, float y) const;
private:
	GameObject(SDL_Rect src);
	//Координаты на поле
	float x;
	float y;
	//Координаты верхнего левого угла прямоугольника,
	// который будет отрисован, на кратинке
	float imageX;
	float imageY;
	float width;
	float height;
	//Прямоугольники, дублирующие верхние переменные
	//прямоугольник, куда рисуется изображение
	SDL_Rect* destRect;
	//определяет, какую часть исходного изображения рисовать
	SDL_Rect* srcRect;
public:
	SDL_Surface* image;
};

#endif /* GAMEOBJECT_H_ */

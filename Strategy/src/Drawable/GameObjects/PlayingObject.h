/*
 * GameObject.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_
#define DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_

#include <iostream>

#include "../../Drawable/GameObject.h"
#include "../../Drawable/GameObjects/Gameplay_Constants.h"
#include "../../Drawable/GameObjects/IPlayingObject.h"

//Базовый класс для юнитов, зданий, и т.д.
class PlayingObject: public Drawable, public IPlayingObject {
public:
	PlayingObject(SDL_Rect src, const char *name_file_image, GameObjectType type=STRUCTURE, float maxSpeed=SPEED_DEFAULT, unsigned int maxHP=HP_DEFAULT, int ownerID=0, Uint8 transparency=255);
	virtual ~PlayingObject();
	//Обновляет состояние (положение) объекта на основе прошедшего времени
	virtual void Update(float time);


	/**
	 * Реализация интерфейса Drowable
	 */
public:
	virtual SDL_Surface* GetImage() const;
	virtual float GetX() const;
	virtual float GetY() const;
	virtual void SetX(float x);
	virtual void SetY(float y);
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual SDL_Rect* GetSrcRect() const;
	virtual SDL_Rect* GetDestRect() const;
	virtual void SetSrcRect(SDL_Rect* src);
	virtual void SetDestRect(SDL_Rect* dest);
	virtual bool ContainsCoordinates(float x, float y) const;
private:
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

	/**
	 * Реализация интерфейса IGameObject
	 */
public:
	virtual GameObjectType GetObjectType();
	virtual unsigned int GetMaxHP();
	virtual unsigned int GetCurrHP();
	virtual void DealDamage(int damage);
	virtual float GetSpeed();
	virtual int GetOwnerID();
	virtual void SetOwnerID(int ID);
	virtual bool IsPicked();
	virtual void SetPicked(bool);
private:
	const GameObjectType ObjectType;
	const float MaxSpeed;
	const unsigned int MaxHP;
	unsigned int currentHP;
	int ownerID;
	bool isPicked;
};

#endif /* DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_LAYINGOBJECT_H_ */

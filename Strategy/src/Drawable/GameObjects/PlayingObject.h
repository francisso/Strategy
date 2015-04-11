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
class PlayingObject: public tempObject, public IPlayingObject {
public:
	PlayingObject(SDL_Rect src, const char *name_file_image,
					GameObjectType type=STRUCTURE, float maxSpeed=SPEED_DEFAULT,
					unsigned int maxHP=HP_DEFAULT, int ownerID=0, Uint8 transparency=255);
	virtual ~PlayingObject() = default;
	//Обновляет состояние (положение) объекта на основе прошедшего времени
	virtual void Update(float time);

	/**
	 * Реализация интерфейса IPlayingObject
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

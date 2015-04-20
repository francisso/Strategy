/*
 * GameObject.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_
#define DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_

#include <iostream>
#include <queue>

#include "../../Constants.h"
#include "../../Drawable/GameObject.h"
#include "../../Drawable/GameObjects/Gameplay_Constants.h"
#include "../../Drawable/GameObjects/IPlayingObject.h"
#include "Action.h"

//Базовый класс для юнитов, зданий, и т.д.
class PlayingObject: public GameObject, public IPlayingObject {
public:
	PlayingObject(SDL_Rect src, const char *name_file_image,
					GameObjectType type=STRUCTURE, float maxSpeed=SPEED_DEFAULT,
					unsigned int maxHP=HP_DEFAULT, int ownerID=0, Uint8 transparency=255);
	virtual ~PlayingObject() = default;
	//Обновляет состояние (положение) объекта на основе прошедшего времени
	virtual void Update(float time);

	/**
	 * Реализация интерфейса IPlayingObject
	 * Описание методов читать там же
	 */
public:
	virtual unsigned int GetMaxHP();
	virtual unsigned int GetCurrHP();
	virtual void DealDamage(int damage);
	virtual float GetMaxSpeed();
	virtual int GetOwnerID();
	virtual void SetOwnerID(int ID);
	virtual bool IsPicked();
	virtual void SetPicked(bool);
	virtual void SetDestX(float destX);
	virtual void SetDestY(float destY);
	virtual float GetDestX();
	virtual float GetDestY();
	virtual Action* GetAction();
	virtual void AddAction(Action* action, bool replace);
	virtual void NextAction();
	virtual void StopNow();
protected:
	const float MaxSpeed;
	const unsigned int MaxHP;
	unsigned int currentHP;
	int ownerID;
	bool isPicked;
	float destX,destY;
	Action* currAction;
	std::queue<Action*> ActionQueue;
};

#endif /* DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_LAYINGOBJECT_H_ */

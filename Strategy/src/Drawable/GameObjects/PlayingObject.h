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

const unsigned int HP_DEFAULT=100u;
const Time RATE_DEFAULT=40.0;
const unsigned int DAMAGE_DEFAULT=5;
const float RANGE_DEFAULT=1.5*CELL_X_PIXELS;

//Базовый класс для юнитов, зданий, и т.д.
class PlayingObject: public GameObject, public IPlayingObject {
public:
	PlayingObject(SDL_Rect src, const char *name_file_image,
					GameObjectType type=BUILDING, float maxSpeed=SPEED_DEFAULT,
					unsigned int maxHP=HP_DEFAULT, Time rate=RATE_DEFAULT,
					unsigned int damage=DAMAGE_DEFAULT, float range=RANGE_DEFAULT,
					int ownerID=0, Uint8 transparency=255);
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
	virtual void AddAction(Action* action, bool replace=true);
	virtual void AddNextAction(Action* action);
	virtual void NextAction();
	virtual void Stop();
	virtual void RepeatLastAction();

	virtual float GetRange();
	virtual Time GetRate();
	virtual unsigned int GetDamage();
protected:
	const float MaxSpeed;
	const unsigned int MaxHP;
	const Time AttackRate;
	const unsigned int Damage;
	const float AttackRange;
	unsigned int currentHP;
	int ownerID;
	bool isPicked;
	float destX,destY;
	Action* currAction;
	std::queue<Action*> ActionQueue;
};

#endif /* DRAWABLE_GAMEOBJECTS_PLAYINGOBJECT_H_LAYINGOBJECT_H_ */

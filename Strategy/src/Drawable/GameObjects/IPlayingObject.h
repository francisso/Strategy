/*
 * IGameObject.h
 *
 *  Created on: Apr 5, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_IPLAYINGOBJECT_H_
#define DRAWABLE_GAMEOBJECTS_IPLAYINGOBJECT_H_

#include "../../Types.h"
#include "Action.h"

class IPlayingObject {
public:
	virtual ~IPlayingObject()=default;
	virtual unsigned int GetMaxHP() =0;
	virtual unsigned int GetCurrHP() =0;
	virtual void DealDamage(int damage) =0;
	virtual float GetMaxSpeed() =0;
	virtual int GetOwnerID() =0;
	virtual void SetOwnerID(int ID) =0;
	virtual bool IsPicked() =0;
	virtual void SetPicked(bool) =0;
	virtual void SetDestX(float destX) =0;
	virtual void SetDestY(float destY) =0;
	virtual float GetDestX() =0;
	virtual float GetDestY() =0;
	virtual Action* GetAction() =0;
	virtual void AddAction(Action* action, bool replace) =0;
	virtual void NextAction() =0;
	virtual void StopNow() =0;
};



#endif /* DRAWABLE_GAMEOBJECTS_IPLAYINGOBJECT_H_ */

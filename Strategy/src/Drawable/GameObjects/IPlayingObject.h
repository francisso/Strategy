/*
 * IGameObject.h
 *
 *  Created on: Apr 5, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_IPLAYINGOBJECT_H_
#define DRAWABLE_GAMEOBJECTS_IPLAYINGOBJECT_H_

#include "../../Types.h"

class IPlayingObject {
public:
	virtual ~IPlayingObject()=default;
//	virtual GameObjectType GetObjectType() =0;
	virtual unsigned int GetMaxHP() =0;
	virtual unsigned int GetCurrHP() =0;
	virtual void DealDamage(int damage) =0;
	virtual float GetSpeed() =0;
	virtual int GetOwnerID() =0;
	virtual void SetOwnerID(int ID) =0;
	virtual bool IsPicked() =0;
	virtual void SetPicked(bool) =0;
};



#endif /* DRAWABLE_GAMEOBJECTS_IPLAYINGOBJECT_H_ */

/*
 * Action.h
 *
 *  Created on: Mar 10, 2015
 *      Author: anton
 */

#ifndef DRAWABLE_GAMEOBJECTS_ACTION_H_
#define DRAWABLE_GAMEOBJECTS_ACTION_H_

#include "../../Rotating.h"
#include "../GameObject.h"

enum ActionType{WAIT,MOVE,ATTACK,PRODUCE_UNIT,PRODUCE_BUILDING};

struct Action{
	ActionType type;
	Direction moveDir;
	GameObject* targetObject;
	Time timeLeft;
	UnitType unit;
	BuildingType building;

	static Action* CreateMoveAction(ActionType type, Direction dir=SOUTH);

	static Action* CreateAttackAction(GameObject* target);
	void ReduceTime(Time t);
	void SetTime(Time t);
	Time GetTime();
};

#endif /* DRAWABLE_GAMEOBJECTS_ACTION_H_ */

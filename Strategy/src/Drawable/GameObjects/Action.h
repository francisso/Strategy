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

#include <memory>

enum ActionType{WAIT,MOVE,ATTACK,PRODUCE_UNIT,PRODUCE_BUILDING};

struct Action{
	ActionType type;
	Direction moveDir;
	//GameObject* targetObject;
	std::shared_ptr<GameObject> targetObject;
	Time timeLeft;
	UnitType unit;
	BuildingType building;

	static Action* CreateMoveAction(ActionType type, Direction dir=SOUTH);

	static Action* CreateAttackAction(GameObject* target);
	void ReduceTime(Time t);
	void SetTime(Time t);
	Time GetTime();
};
/*
const Action* const Wait = new Action(WAIT,true);
const Action* MoveRight=Action(MOVE_HORIZONTAL,true);
const Action* MoveLeft=Action(MOVE_HORIZONTAL,false);
const Action* MoveUp=Action(MOVE_VERTICAL,false);
const Action* MoveDown=Action(MOVE_VERTICAL,true);*/

#endif /* DRAWABLE_GAMEOBJECTS_ACTION_H_ */

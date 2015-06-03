/*
 * Action.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: staslatgttt
 */

#include "Action.h"

Action* Action::CreateMoveAction(ActionType type,Direction dir){
	Action* action = new Action();
	action->type=type;
	action->moveDir=dir;
	action->targetObject=nullptr;
	action->timeLeft=0;
	action->building=TOWER;
	action->unit=ARCHER;
	return action;
}

void Action::ReduceTime(Time t){
	if(timeLeft>t)
		timeLeft-=t;
	else
		timeLeft=0.0;
}

Time Action::GetTime(){
	return this->timeLeft;
}

void Action::SetTime(Time t) {
	this->timeLeft=t;
}

Action* Action::CreateAttackAction(GameObject* target){
	if(target->GetObjectType()==ENVIRONMENT || target->GetObjectType()==LOOT) return CreateMoveAction(WAIT);
	Action* action = new Action();
	action->type=ATTACK;
	action->targetObject=target;
	action->timeLeft=0.0;
	return action;
}

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
	action->time=0;
	action->building=TOWER;
	action->unit=ARCHER;
	return action;
}

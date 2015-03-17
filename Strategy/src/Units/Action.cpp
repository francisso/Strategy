/*
 * Action.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: staslatgttt
 */

#include "Action.h"

Action* MoveRight(){
	Action* action = new Action();
	action->actionType=Action::MOVE_HORIZONTAL;
	action->IsPositive=true;
	return action;
}

Action* MoveLeft(){
	Action* action = new Action();
	action->actionType=Action::MOVE_HORIZONTAL;
	action->IsPositive=false;
	return action;
}

Action* MoveUp(){
	Action* action = new Action();
	action->actionType=Action::MOVE_VERTICAL;
	action->IsPositive=false;
	return action;
}

Action* MoveDown(){
	Action* action = new Action();
	action->actionType=Action::MOVE_VERTICAL;
	action->IsPositive=true;
	return action;
}

Action* Stay(){
	Action* action = new Action();
	action->actionType=Action::STAY;
	action->IsPositive=true;
	return action;
}


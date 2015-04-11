/*
 * Action.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: staslatgttt
 */

#include "../../../Drawable/GameObjects/Units/Action.h"

Action* Action::CreateAction(ActionType type,bool isPositive){
	Action* action = new Action();
	action->type=type;
	action->isPositive=isPositive;
	return action;
}


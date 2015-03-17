/*
 * Action.h
 *
 *  Created on: Mar 10, 2015
 *      Author: anton
 */

#ifndef UNITS_ACTION_H_
#define UNITS_ACTION_H_

#include "Unit.h"


struct Action{
	enum Actions{STAY,MOVE_VERTICAL,MOVE_HORIZONTAL, ATTACK};
	Actions actionType;
	//this should be a pointer to a Unit but it doesn't work
	void* who;
	bool IsPositive;
};

Action* MoveRight();

Action* MoveLeft();

Action* MoveUp();

Action* MoveDown();

Action* Stay();

#endif /* UNITS_ACTION_H_ */

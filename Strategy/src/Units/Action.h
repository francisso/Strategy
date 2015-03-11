/*
 * Action.h
 *
 *  Created on: Mar 10, 2015
 *      Author: anton
 */

#ifndef UNITS_ACTION_H_
#define UNITS_ACTION_H_

#include "Unit.h"


struct Action {
	enum Actions{MOVE, ATTACK};
	Actions actionType;
	//this should be a pointer to a Unit but it doesn't work
	void* who;
};

struct ActionMove : public Action {
	float x_speed;
	float y_speed;
};



#endif /* UNITS_ACTION_H_ */

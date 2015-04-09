/*
 * Action.h
 *
 *  Created on: Mar 10, 2015
 *      Author: anton
 */

#ifndef DROWABLE_GAMEOBJECTS_UNITS_ACTION_H_
#define DROWABLE_GAMEOBJECTS_UNITS_ACTION_H_

#include "Unit.h"

enum ActionType{STAY,MOVE_VERTICAL,MOVE_HORIZONTAL, ATTACK};

struct Action{
	ActionType type;
	//this should be a pointer to a Unit but it doesn't work
	void* who;
	bool isPositive;

	/**
	 * @CreateAction возвращает указатель на нужный тип @Action
	 * @type и @IsPositive записываются в соответствующие поля @Action
	 */
	static Action* CreateAction(ActionType type,bool isPositive=true);
};

#endif /* DROWABLE_GAMEOBJECTS_UNITS_ACTION_H_ */

/*
 * Unit.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "../GameObject.h"
#include "Action.h"

class Unit : public GameObject{
public:
	virtual ~Unit()=default;
	Unit(SDL_Rect src, const char *name_file_image);
	Action* GetAction();
	void SetAction(Action* action);
private:
	Action* action;
};

#endif /* UNIT_H_ */

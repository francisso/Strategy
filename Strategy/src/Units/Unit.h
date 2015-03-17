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
#include "../Constants.h"
#include <cmath>
#include <queue>

class Unit : public GameObject{
public:
	virtual ~Unit()=default;
	Unit(SDL_Rect src, const char *name_file_image);
	struct Action* GetAction();
	void AddAction(struct Action* action, bool replace=true);
	void NextAction();
	float GetMaxSpeed();
	void MoveToCell(int x_target,int y_target,bool replace=true);
private:
	struct Action* action;
	std::queue<struct Action*> ActionQueue;
	float MaxSpeed;
};

#endif /* UNIT_H_ */

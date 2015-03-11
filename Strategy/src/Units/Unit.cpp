/*
 * Unit.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "Unit.h"

Unit::Unit(SDL_Rect src, const char *name_file_image) : GameObject(src, name_file_image) {
	//TODO this initialization is a developer version
	auto action = new ActionMove();
	action->actionType= Action::MOVE;
	action->who = this;
	action->x_speed = 1.0f;
	action->y_speed = 0.0f;
	this->action = action;
}

Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

Action* Unit::GetAction() {
	return action;
}

void Unit::SetAction(Action* action) {
	this->action = action;
}

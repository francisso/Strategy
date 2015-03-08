/*
 * Unit.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "Unit.h"

Unit::Unit(SDL_Rect src, const char *name_file_image) : GameObject(src, name_file_image) {
	//TODO this initialization is a develop version
	xSpeed = 1.0f;
	ySpeed = 1.0f;
}
Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

void Unit::Update(float time) {
	this->setX(this->X()+time*xSpeed);
	this->setY(this->Y()+time*ySpeed);
}

/*
 * Environment.h
 *
 *  Created on: Apr 9, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_ENVIRONMENT_H_
#define DRAWABLE_GAMEOBJECTS_ENVIRONMENT_H_

#include "../../Drawable/GameObject.h"
#include "Sizeable.h"

class Environment: public GameObject, public Sizeable{
private:
	EnvironmentType type;
public:
	Environment(SDL_Rect src, const char* name_file_image, EnvironmentType type, unsigned int sizeX, unsigned int sizeY, Uint8 transparency=255);
	EnvironmentType WhatIs();
};



#endif /* DRAWABLE_GAMEOBJECTS_ENVIRONMENT_H_ */

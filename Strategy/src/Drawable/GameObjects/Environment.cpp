/*
 * Environment.cpp
 *
 *  Created on: May 21, 2015
 *      Author: staslatgttt
 */

#include "Environment.h"

Environment::Environment(SDL_Rect src, const char* name_file_image, EnvironmentType type, unsigned int sizeX, unsigned int sizeY, Uint8 transparency):
	GameObject(src, name_file_image, ENVIRONMENT, transparency), Sizeable(sizeX, sizeY), type(type){}

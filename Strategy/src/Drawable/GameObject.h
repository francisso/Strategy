/*
 * GameObject.h
 *
 *  Created on: Apr 9, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECT_H_
#define DRAWABLE_GAMEOBJECT_H_

#include "Draw.h"

class tempObject: public Draw{
public:
	tempObject(SDL_Rect src, const char *name_file_image, Uint8 transparency);
	~tempObject() = default;
};

#endif /* DRAWABLE_GAMEOBJECT_H_ */

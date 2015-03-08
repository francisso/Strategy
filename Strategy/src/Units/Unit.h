/*
 * Unit.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "../GameObject.h"

class Unit : public GameObject{
public:
	virtual ~Unit();
	Unit(SDL_Rect src, const char *name_file_image);
	virtual void Update(float time);
protected:
	float xSpeed;
	float ySpeed;
};

#endif /* UNIT_H_ */

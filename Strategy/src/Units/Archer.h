/*
 * Archers.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef ARCHERS_H_
#define ARCHERS_H_

#include "Unit.h"
#include "SDL/SDL.h"

class Archer: public Unit {
public:
	virtual ~Archer();
	Archer(SDL_Rect src, const char *name_file_image) : Unit(src, name_file_image) {};

};

#endif /* ARCHERS_H_ */

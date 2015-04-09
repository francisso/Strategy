/*
 * Archers.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef ARCHERS_H_
#define ARCHERS_H_

#include "SDL/SDL.h"
#include "Unit.h"

class Archer: public Unit {
public:
	virtual ~Archer()=default;
	Archer(SDL_Rect src, const char *name_file_image, int ownerID=0) : Unit(src, name_file_image,SPEED_ARCHER_DEFAULT,HP_ARCHER_DEFAULT,ownerID) {};

};

#endif /* ARCHERS_H_ */

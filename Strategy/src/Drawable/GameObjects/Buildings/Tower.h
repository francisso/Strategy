/*
 * Tower.h
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_BUILDINGS_TOWER_H_
#define DRAWABLE_GAMEOBJECTS_BUILDINGS_TOWER_H_

#include "../Buildings/Building.h"

class Tower: public Building{
public:
	Tower(SDL_Rect stc,const char *name_file_image, int ownerID=0);
	~Tower()=default;
};



#endif /* DRAWABLE_GAMEOBJECTS_BUILDINGS_TOWER_H_ */

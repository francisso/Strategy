/*
 * Building.h
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_BUILDINGS_BUILDING_H_
#define DRAWABLE_GAMEOBJECTS_BUILDINGS_BUILDING_H_

#include "../PlayingObject.h"

enum Buildings{TOWER,FORT};

class Building: public PlayingObject{
public:
	Building(SDL_Rect src, const char *name_file_image, Buildings buildingType, float maxSpeed=SPEED_DEFAULT,unsigned int maxHP=HP_BUILDING_DEFAULT,int ownerID=0,int SizeX=X_BUILDING_DEFAULT, int SizeY=Y_BUILDING_DEFAULT);
	~Building()=default;
	unsigned int GetSizeX();
	unsigned int GetSizeY();

	virtual Buildings WhatIs();
private:
	const Buildings whatIs;
	const unsigned int SizeX, SizeY;
};



#endif /* DRAWABLE_GAMEOBJECTS_BUILDINGS_BUILDING_H_ */

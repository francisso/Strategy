/*
 * Building.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#include "../Buildings/Building.h"

Building::Building(SDL_Rect src, const char *name_file_image,float maxSpeed,unsigned int maxHP,int ownerID,int sizeX, int sizeY):
														PlayingObject(src, name_file_image,BUILDING,maxSpeed,maxHP,ownerID),SizeX(sizeX),SizeY(sizeY){}

unsigned int Building::GetSizeX(){return SizeX;}

unsigned int Building::GetSizeY(){return SizeY;}





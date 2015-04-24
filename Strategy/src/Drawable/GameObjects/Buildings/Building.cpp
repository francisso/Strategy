/*
 * Building.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#include "../Buildings/Building.h"

Building::Building(SDL_Rect src, const char *name_file_image, Buildings buildingType, float maxSpeed,unsigned int maxHP,int ownerID,int sizeX, int sizeY):
														PlayingObject(src, name_file_image,BUILDING,maxSpeed,maxHP,ownerID),whatIs(buildingType),SizeX(sizeX),SizeY(sizeY){}

unsigned int Building::GetSizeX(){return SizeX;}

unsigned int Building::GetSizeY(){return SizeY;}

Buildings Building::WhatIs(){return whatIs;}





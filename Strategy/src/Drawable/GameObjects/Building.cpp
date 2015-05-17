/*
 * Building.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#include "Building.h"

Building::Building(SDL_Rect src, const char *name_file_image, BuildingType buildingType, float maxSpeed,unsigned int maxHP,int ownerID,int sizeX, int sizeY):
														PlayingObject(src, name_file_image,BUILDING,maxSpeed,maxHP,ownerID),Sizeable(sizeX, sizeY), whatIs(buildingType){}

BuildingType Building::WhatIs(){return whatIs;}

void Building::SetX(float x){
	PlayingObject::SetX(x);
}

void Building::SetY(float y){
	PlayingObject::SetY(y);
}





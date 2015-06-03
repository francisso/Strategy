/*
 * Building.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#include "Building.h"

Building::Building(SDL_Rect src, const char *name_file_image,
		BuildingType buildingType, float maxSpeed,unsigned int maxHP,
		Time rate, unsigned int damage, float range, int ownerID,
		int sizeX, int sizeY):
														PlayingObject(src, name_file_image,BUILDING,
																maxSpeed,maxHP,rate, damage, range, ownerID),
														Sizeable(sizeX, sizeY),
														whatIs(buildingType){

}

BuildingType Building::WhatIs() {
	return whatIs;
}

void Building::SetX(float x){
	PlayingObject::SetX(x);
}

void Building::SetY(float y){
	PlayingObject::SetY(y);
}

void Building::Produce(UnitType type, bool replace){
	//std::cout<<"Queue freed"<<std::endl;
	Action* action=new Action();
	action->timeLeft=10.0;
	action->unit=type;
	action->building=TOWER;
	action->type=PRODUCE_UNIT;
	action->targetObject=nullptr;
	action->moveDir=SOUTH;
	std::cout<<"Before adding action"<<std::endl;
	PlayingObject::AddAction(action, replace);
	std::cout<<"Action added"<<std::endl;
}

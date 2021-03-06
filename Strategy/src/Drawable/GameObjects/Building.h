/*
 * Building.h
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_BUILDING_H_
#define DRAWABLE_GAMEOBJECTS_BUILDING_H_

#include "PlayingObject.h"
#include "Sizeable.h"



class Building: public PlayingObject, public Sizeable{
public:
	Building(SDL_Rect src, const char *name_file_image,
			BuildingType buildingType, float maxSpeed=SPEED_DEFAULT,
			unsigned int maxHP=HP_BUILDING_DEFAULT,
			Time rate=RATE_DEFAULT, unsigned int damage=DAMAGE_DEFAULT,
			float range=RANGE_DEFAULT, int ownerID=0,int SizeX=X_BUILDING_DEFAULT,
			int SizeY=Y_BUILDING_DEFAULT);
	~Building()=default;

	virtual BuildingType WhatIs();

	virtual void SetX(float x);
	virtual void SetY(float y);

	/**
	 * Добавляет Action, который будет обрабатываться Game и приведет к созданию Unit типа type
	 * @replace - если true, очищает очередь перед добавлением нового Action
	 */
	void Produce(UnitType type, bool replace=false);
private:
	const BuildingType whatIs;
};



#endif /* DRAWABLE_GAMEOBJECTS_BUILDING_H_ */

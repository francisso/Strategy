/*
 * ObjectFactory.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: staslatgttt
 */

#include "ObjectFactory.h"

Unit* ObjectFactory::CreateUnit(UnitType type,int ownerID, float x, float y)
{
	UnitProperties* currUnit;
	switch(type){
	case ARCHER:
		if(ArcherProps==nullptr) ArcherProps=LoadUnitFromXML(ARCHER);
		currUnit=ArcherProps;
		break;
	case SWORDMAN:
		if(SwordmanProps==nullptr) SwordmanProps=LoadUnitFromXML(SWORDMAN);
		currUnit=SwordmanProps;
		break;
	default:
		return nullptr;
	}
	if(currUnit==nullptr) return nullptr;
	SDL_Rect* src = new SDL_Rect{0,0,CELL_X_PIXELS,CELL_Y_PIXELS};
	Unit* unit= new Unit(*src,currUnit->imageFile,type,currUnit->MaxSpeed,currUnit->MaxHP,ownerID);
	unit->SetX(x);
	unit->SetY(y);
	return unit;
}

UnitProperties* ObjectFactory::LoadUnitFromXML(UnitType type)
{
	UnitProperties* unitProps=new UnitProperties;

	if(type) return nullptr;
	return unitProps;
}

/*
 * ObjectFactory.h
 *
 *  Created on: Apr 24, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_
#define DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_

#include "../../../lib/rapidxml-1.13/rapidxml.hpp"
#include "./Units/Unit.h"
#include "./Buildings/Building.h"
#include "./Loot.h"
#include "./Environment.h"

struct UnitProperties{
	UnitType type;
	char *imageFile;
	float MaxSpeed;
	unsigned int MaxHP;
	unsigned int Damage;
	float AttackRange;
};

struct BuildingProperties{
	BuildingType type;
	char *imageFile;
	unsigned int MaxHP;
	unsigned int Damage;
	float AttackRange;
	unsigned int SizeX;
	unsigned int SizeY;
};

class ObjectFactory{
private:
	static const char *unitConfigs, *buildingConfigs, *lootConfigs, *environmentConfigs;
	static UnitProperties *ArcherProps,*SwordmanProps;
	static BuildingProperties *TowerProps, *FortProps;
public:

	static UnitProperties* LoadUnitFromXML(UnitType unitType);
	static BuildingProperties* LoadBuildingFromXML(BuildingType buildingType);

	/**
	 * Создание юнита по шаблону
	 */
	static Unit* CreateUnit(UnitType type,int ownerID, float x=0.0f, float y=0.0f);

	/**
	 * Создание здания по шаблону
	 */
	static Building* CreateBuilding(BuildingType type, int ownerID, float x=0.0f, float y=0.0f);

	/**
	 * Методы создания лута
	 */

	/**
	 * Методы создания окружения
	 */
};

const char* ObjectFactory::unitConfigs="ObjectConfigs/Units.xml";
const char* ObjectFactory::buildingConfigs="ObjectConfigs/Buildings.xml";
const char* ObjectFactory::lootConfigs="ObjectConfigs/Loot.xml";
const char* ObjectFactory::environmentConfigs="ObjectConfigs/Environment.xml";

UnitProperties *ObjectFactory::ArcherProps;
UnitProperties *ObjectFactory::SwordmanProps;

#endif /* DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_ */

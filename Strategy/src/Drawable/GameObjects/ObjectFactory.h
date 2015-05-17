/*
 * ObjectFactory.h
 *
 *  Created on: Apr 24, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_
#define DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_


#ifndef RAPID_XML_
#define RAPID_XML_
#include "../../../lib/rapidxml-1.13/rapidxml.hpp"
//#include "../../../lib/rapidxml-1.13/rapidxml_utils.hpp"
#endif

#include <fstream>
#include <cstdlib>

#include "Unit.h"
#include "Building.h"
#include "./Loot.h"
#include "./Environment.h"

using namespace rapidxml;

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
	//static UnitProperties ArcherProps,SwordmanProps;
	//static BuildingProperties TowerProps, FortProps;
	static const char* abc;

public:

	static UnitProperties LoadUnitFromXML(UnitType unitType);
	static BuildingProperties LoadBuildingFromXML(BuildingType buildingType);

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

#endif /* DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_ */

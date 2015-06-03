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
#include <string>

#include "Unit.h"
#include "Building.h"
#include "Loot.h"
#include "Environment.h"

using namespace rapidxml;

struct UnitProperties{
	UnitType type;
	std::string imageFile;
	float MaxSpeed;
	unsigned int MaxHP;
	Time AttackRate;
	unsigned int Damage;
	float AttackRange;
};

struct BuildingProperties{
	BuildingType type;
	std::string imageFile;
	unsigned int MaxHP;
	Time AttackRate;
	unsigned int Damage;
	float AttackRange;
	unsigned int SizeX;
	unsigned int SizeY;
};

struct LootProperties{
	LootType type;
	std::string imageFile;
	int amount;
};

struct EnvironmentProperties{
	EnvironmentType type;
	std::string imageFile;
	unsigned int SizeX;
	unsigned int SizeY;
};

class ObjectFactory{
private:
	static const char *unitConfigs, *buildingConfigs, *lootConfigs, *environmentConfigs;
	//static UnitProperties ArcherProps,SwordmanProps
	//static BuildingProperties TowerProps, FortProps;
	static const char* abc;

public:

	static UnitProperties LoadUnitFromXML(UnitType type);
	static BuildingProperties LoadBuildingFromXML(BuildingType type);
	static LootProperties LoadLootFromXML(LootType type);
	static EnvironmentProperties LoadEnvironmentFromXML(EnvironmentType type);

	/**
	 * Создание юнита по шаблону
	 */
	static Unit* CreateUnit(UnitType type,int ownerID, float x=0.0f, float y=0.0f);

	/**
	 * Создание здания по шаблону
	 */
	static Building* CreateBuilding(BuildingType type, int ownerID, float x=0.0f, float y=0.0f);

	/**
	 * Создание лута по шаблону
	 */
	static Loot* CreateLoot(LootType type, float x=0.0f, float y=0.0f);

	/**
	 * Создание окружения по шаблону
	 */
	static Environment* CreateEnvironment(EnvironmentType type, float x=0.0f, float y=0.0f);
};

#endif /* DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_ */

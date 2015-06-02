/*
 * ObjectFactory.cpp
 *
 *  Created on: Apr 30, 2015
 *      Author: staslatgttt
 */

#include "ObjectFactory.h"

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Units
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

Unit* ObjectFactory::CreateUnit(UnitType type,int ownerID, float x, float y)
{
	UnitProperties currUnit;
	static UnitProperties ArcherProps=LoadUnitFromXML(ARCHER);
	static UnitProperties SwordmanProps=LoadUnitFromXML(SWORDMAN);
	switch(type){
	case ARCHER:
		currUnit=ArcherProps;
		break;
	case SWORDMAN:
		currUnit=SwordmanProps;
		break;
	default:
		return nullptr;
	}
	SDL_Rect src = {0,0,CELL_X_PIXELS,CELL_Y_PIXELS};
	Unit* unit= new Unit(src,currUnit.imageFile.c_str(),type,currUnit.MaxSpeed,currUnit.MaxHP,ownerID);
	unit->SetX(x);
	unit->SetY(y);
	return unit;
}



UnitProperties ObjectFactory::LoadUnitFromXML(UnitType type)
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile ("res/object_configs/Units.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	switch (type) {
	case ARCHER: root_node = doc.first_node("Archer"); break;
	case SWORDMAN: root_node = doc.first_node("Swordman"); break;
	}
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml\n");

	auto imageFile =std::string(root_node->first_attribute("imageFile")->value());
	auto AttackRange = strtof (root_node->first_attribute("AttackRange")->value(), NULL);
	auto Damage = static_cast<unsigned int>(strtoul(root_node->first_attribute("Damage")->value(),NULL,10));
	auto MaxHP = static_cast<unsigned int>(strtoul(root_node->first_attribute("MaxHP")->value(), NULL,10));
	auto MaxSpeed = strtof (root_node->first_attribute("MaxSpeed")->value(),  NULL);

	return {type,imageFile, MaxSpeed, MaxHP,Damage,AttackRange};
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Buildings
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

Building* ObjectFactory::CreateBuilding(BuildingType type,int ownerID, float x, float y)
{
	BuildingProperties* currBuilding = new BuildingProperties();
	static BuildingProperties TowerProps=LoadBuildingFromXML(TOWER);
	static BuildingProperties FortProps=LoadBuildingFromXML(FORT);
	switch(type){
	case TOWER:
		*currBuilding=TowerProps;
		break;
	case SWORDMAN:

		*currBuilding=FortProps;
		break;
	default:
		return nullptr;
	}
	SDL_Rect* src = new SDL_Rect{0,0,static_cast<Uint16>(CELL_X_PIXELS*currBuilding->SizeX),static_cast<Uint16>(CELL_Y_PIXELS*currBuilding->SizeY)};
	Building* building= new Building(*src,currBuilding->imageFile.c_str(),type,SPEED_DEFAULT,currBuilding->MaxHP,ownerID, currBuilding->SizeX, currBuilding->SizeY);
	building->SetX(x);
	building->SetY(y);
	return building;
}



BuildingProperties ObjectFactory::LoadBuildingFromXML(BuildingType type)
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile ("res/object_configs/Buildings.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	switch (type) {
	case TOWER: root_node = doc.first_node("Tower"); break;
	case FORT: root_node = doc.first_node("Fort"); break;
	}
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml\n");

	auto imageFile = std::string(root_node->first_attribute("imageFile")->value());
	auto AttackRange = strtof (root_node->first_attribute("AttackRange")->value(), NULL);
	auto Damage = static_cast<unsigned int>(strtoul(root_node->first_attribute("Damage")->value(),NULL,10));
	auto MaxHP = static_cast<unsigned int>(strtoul(root_node->first_attribute("MaxHP")->value(), NULL,10));
	auto SizeX = static_cast<unsigned int>(strtoul(root_node->first_attribute("SizeX")->value(), NULL,10));
	auto SizeY = static_cast<unsigned int>(strtoul(root_node->first_attribute("SizeY")->value(), NULL,10));

	return {type,imageFile, MaxHP,Damage,AttackRange,SizeX,SizeY};
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Loot
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

Loot* ObjectFactory::CreateLoot(LootType type, float x, float y)
{
	LootProperties* currLoot = new LootProperties();
	static LootProperties GoldProps=LoadLootFromXML(GOLD);
	switch(type){
	case GOLD:
		*currLoot=GoldProps;
		break;
	default:
		return nullptr;
	}
	SDL_Rect* src = new SDL_Rect{0,0,CELL_X_PIXELS,CELL_Y_PIXELS};
	Loot* loot= new Loot(*src,currLoot->imageFile.c_str(), currLoot->type, currLoot->amount);
	loot->SetX(x);
	loot->SetY(y);
	return loot;
}



LootProperties ObjectFactory::LoadLootFromXML(LootType type)
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile ("res/object_configs/Loot.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	switch (type) {
	case GOLD: root_node = doc.first_node("Gold"); break;
	}
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml\n");

	auto imageFile = std::string(root_node->first_attribute("imageFile")->value());
	auto Amount = static_cast<int>(strtoul(root_node->first_attribute("amount")->value(),NULL,10));

	return {type,imageFile,Amount};
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Environment
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

Environment* ObjectFactory::CreateEnvironment(EnvironmentType type, float x, float y)
{
	EnvironmentProperties* currEnvironment = new EnvironmentProperties();
	static EnvironmentProperties StoneProps=LoadEnvironmentFromXML(STONE);
	static EnvironmentProperties TreesProps=LoadEnvironmentFromXML(TREES);
	static EnvironmentProperties BrushProps=LoadEnvironmentFromXML(BRUSH);
	switch(type){
	case STONE:
		*currEnvironment=StoneProps;
		break;
	case TREES:
		*currEnvironment=TreesProps;
		break;
	case BRUSH:
		*currEnvironment=BrushProps;
		break;
	default:
		return nullptr;
	}
	SDL_Rect* src = new SDL_Rect{0,0,static_cast<Uint16>(CELL_X_PIXELS*currEnvironment->SizeX),static_cast<Uint16>(CELL_Y_PIXELS*currEnvironment->SizeY)};
	Environment* environment= new Environment(*src, currEnvironment->imageFile.c_str(), currEnvironment->type, currEnvironment->SizeX, currEnvironment->SizeY);
	environment->SetX(x);
	environment->SetY(y);
	return environment;
}



EnvironmentProperties ObjectFactory::LoadEnvironmentFromXML(EnvironmentType type)
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile ("res/object_configs/Environment.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	switch (type) {
	case STONE: root_node = doc.first_node("Stone"); break;
	case TREES: root_node = doc.first_node("Trees"); break;
	case BRUSH: root_node = doc.first_node("Brush"); break;
	}
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml\n");

	auto imageFile =std::string(root_node->first_attribute("imageFile")->value());
	std::cout<<imageFile<<std::endl;
	auto SizeX = static_cast<unsigned int>(strtoul(root_node->first_attribute("sizeX")->value(),NULL,10));
	auto SizeY = static_cast<unsigned int>(strtoul(root_node->first_attribute("sizeY")->value(),NULL,10));

	return {type,imageFile,SizeX, SizeY};
}

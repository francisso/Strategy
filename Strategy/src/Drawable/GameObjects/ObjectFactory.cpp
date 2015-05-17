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
	std::ifstream theFile ("ObjectConfigs/Units.xml");
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
	Building* building= new Building(*src,currBuilding->imageFile,type,SPEED_DEFAULT,currBuilding->MaxHP,ownerID, currBuilding->SizeX, currBuilding->SizeY);
	building->SetX(x);
	building->SetY(y);
	return building;
}



BuildingProperties ObjectFactory::LoadBuildingFromXML(BuildingType type)
{
	xml_document<> doc;
	xml_node<> * root_node;

	// Read the xml file into a vector
	std::ifstream theFile ("ObjectConfigs/Buildings.xml");
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

	auto imageFile = root_node->first_attribute("imageFile")->value();
	auto AttackRange = strtof (root_node->first_attribute("AttackRange")->value(), NULL);
	auto Damage = static_cast<unsigned int>(strtoul(root_node->first_attribute("Damage")->value(),NULL,10));
	auto MaxHP = static_cast<unsigned int>(strtoul(root_node->first_attribute("MaxHP")->value(), NULL,10));
	auto SizeX = static_cast<unsigned int>(strtoul(root_node->first_attribute("SizeX")->value(), NULL,10));
	auto SizeY = static_cast<unsigned int>(strtoul(root_node->first_attribute("SizeY")->value(), NULL,10));

	return {type,imageFile, MaxHP,Damage,AttackRange,SizeX,SizeY};
}

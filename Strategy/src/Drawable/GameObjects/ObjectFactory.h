/*
 * ObjectFactory.h
 *
 *  Created on: Apr 24, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_
#define DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_

#include "../../lib/rapidxml-1.13/rapidxml.hpp"
#include "./Units/Unit.h"
#include "./Buildings/Building.h"
#include "./Loot.h"
#include "./Environment.h"

class ObjectFactory{
public:
	/**
	 * Методы создания юнитов
	 * Добавляя метод, не забудь добавить соответствующее значение в перечисление Units в файле Unit.h
	 */
	static Unit* CreateArcher(int ownerID, float x=0.0f, float y=0.0f);
	static Unit* CreateSwordman(int ownerID, float x=0.0f, float y=0.0f);

	/**
	 * Методы создания зданий
	 * Добавляя метод, не забудь добавить соответствующее значение в перечисление Buildings в файле Building.h
	 */
	static Building* CreateTower(int ownerID, float x=0.0f, float y=0.0f);
	static Building* CreateFort(int ownerID, float x=0.0f, float y=0.0f);

	/**
	 * Методы создания лута
	 */

	/**
	 * Методы создания окружения
	 */
};



#endif /* DRAWABLE_GAMEOBJECTS_OBJECTFACTORY_H_ */

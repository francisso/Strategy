/*
 * Types.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <SDL/SDL_events.h>
#include <inttypes.h>
//Временные типы, переопределить по необходимости
typedef float Time;

//Виды текстур на поле
enum TextureType {GROUND, WATER, SAND, FOREST, MOUNTIAN, SWAMP};

//Возможные состояния клетки
enum CellType {NOTHING, OBJECT, OBJECT_PART};

//Кому может быть адресованно событие
enum ReceiverType {GAME, STATUS_BAR_AMOUNT, STATUS_BAR_ACTION, STATUS_BAR_GOLD};
enum OrderType {SELECTED};

//Возможные классы объектов на карте
enum GameObjectType {UNIT,BUILDING,LOOT,ENVIRONMENT};

enum UnitType{ARCHER, SWORDMAN};
enum BuildingType{TOWER,FORT};
enum EnvironmentType{TREES,STONE,BRUSH};
enum LootType{GOLD};
#endif /* TYPES_H_ */

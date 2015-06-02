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


enum TextureType {GROUND, WATER, SAND, FOREST, MOUNTIAN, SWAMP};

enum CellType {NOTHING, OBJECT, OBJECT_PART};

enum ReceiverType {GAME, STATUS_BAR_AMOUNT, STATUS_BAR_ACTION};
enum OrderType {SELECTED};

enum GameObjectType {UNIT,BUILDING,LOOT,ENVIRONMENT};

enum UnitType{ARCHER, SWORDMAN};
enum BuildingType{TOWER,FORT};
enum EnvironmentType{TREES,STONE,BRUSH};
enum LootType{GOLD};
#endif /* TYPES_H_ */

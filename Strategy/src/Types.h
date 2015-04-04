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
typedef float CoordinateType;
typedef float Time;


enum TextureType {GROUND, WATER, SAND, FOREST, MOUNTIAN, SWAMP};
//OCCUPIED - состояние, когда юнит переходит на эту клетку.
enum CellType{NOTHING, UNIT, OCCUPIED, BUILDING};

struct EventForPlayer{
	SDL_Event* event;
	int cell_x;
	int cell_y;
	//TODO проверить на дополнительные параметры, поставленные к передаче
};
#endif /* TYPES_H_ */

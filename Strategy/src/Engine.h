/*
 * Engine.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <SDL/SDL.h>

#include "Drawable.h"

//Временный тип, когда станет известно, изменить на нужный
typedef int StructureType;

//Engine отвечает за отрисовку
class Engine {
public:
	Engine();
	virtual ~Engine();
	bool AddDrawable(Drawable*);
	bool DeleteDrawable(Drawable*);
private:
	//Структура, хранящая объекты для отрисовки
	StructureType toDraw;

};

#endif /* ENGINE_H_ */

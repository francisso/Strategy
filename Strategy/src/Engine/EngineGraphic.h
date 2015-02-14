/*
 * EngineGraphic.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef ENGINE_GRAPHIC_H_
#define ENGINE_GRAPHIC_H_

#include <SDL/SDL.h>

#include "../Drawable.h"
#include "../Types.h"

//Временный тип, когда станет известно, изменить на нужный
typedef int StructureType;

//Engine отвечает за отрисовку
class EngineGraphic {
public:
	EngineGraphic();
	virtual ~EngineGraphic();
	bool Draw(Drawable* drawable, CoordinateType x, CoordinateType y);
};

#endif /* ENGINE_GRAPHIC_H_ */

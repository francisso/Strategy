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
	friend class Engine;

public:
	EngineGraphic();
	virtual ~EngineGraphic();

	//возвращет true, если отрисовка удачна.
	//Возможно, void будет удобнее
	bool Draw(Drawable* drawable);

private:
	//Поверхность, на которую осуществляется отрисовка
	SDL_Surface* screen;
};

#endif /* ENGINE_GRAPHIC_H_ */

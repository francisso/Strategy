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
	bool Draw(Drawable* drawable);

	//Создает SDL_Surface с заданным текстом, готовую для отрисовки на экран
	//набор аргументов приблизительный
	static SDL_Surface* GetSurfaceFromText(char* text, int size);

private:
	//Поверхность, на которую осуществляется отрисовка
	SDL_Surface* screen;
};

#endif /* ENGINE_GRAPHIC_H_ */

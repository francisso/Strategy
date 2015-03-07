/*
 * SurfaceFactory.h
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#ifndef ENGINE_SURFACEFACTORY_H_
#define ENGINE_SURFACEFACTORY_H_

#include <SDL/SDL.h>

//Фабрика, создающая примитивы для SDL
class SurfaceFactory {
public:
	//Создает новую SDL_Surface
	//с текстом в заданных координатах
	//static SDL_Surface* CreateFromText(char* text, int size, Uint16 x, Uint16 y);

private:
	SurfaceFactory();
	virtual ~SurfaceFactory();
};

#endif /* ENGINE_SURFACEFACTORY_H_ */

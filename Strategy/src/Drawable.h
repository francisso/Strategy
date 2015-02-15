/*
 * Drawable.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <SDL/SDL.h>

#include "Types.h"


//Базовый интерфейс для любого объекта,
//который может быть отрисован
class  Drawable {
public:
	Drawable();
	virtual ~Drawable();
	virtual SDL_Surface* GetImage() = 0;
	virtual CoordinateType X() =0;
	virtual CoordinateType Y() =0;
	virtual CoordinateType GetWidth() = 0;
	virtual CoordinateType GetHeight() = 0;
	virtual SDL_Rect* GetSrcRect() = 0;
	virtual SDL_Rect* GetDestRect() = 0;

};

#endif /* DRAWABLE_H_ */

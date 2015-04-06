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
	virtual ~Drawable()=default;
	virtual SDL_Surface* GetImage() const =0;
//	virtual void SetImage(SDL_Surface* image) = 0;
	virtual float GetX() const =0;
	virtual float GetY() const =0;
	virtual void SetX(float x) =0;
	virtual void SetY(float y) =0;
	virtual float GetWidth() const =0;
	virtual float GetHeight() const =0;
	virtual SDL_Rect* GetSrcRect() const =0;
	virtual SDL_Rect* GetDestRect() const =0;
	//returns true if this Drawable contains coordinates
	virtual bool ContainsCoordinates(float x, float y) const =0;
};

#endif /* DRAWABLE_H_ */

/*
 * Drow.h
 *
 *  Created on: Apr 9, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_DRAW_H_
#define DRAWABLE_DRAW_H_

#include "../IDrawable.h"

class Draw: public Drawable{
public:
	Draw(SDL_Rect src, const char *name_file_image, Uint8 transparency = 255);
	virtual ~Draw();
	virtual SDL_Surface* GetImage() const;
	virtual float GetX() const;
	virtual float GetY() const;
	virtual void SetX(float x);
	virtual void SetY(float y);
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual SDL_Rect* GetSrcRect() const;
	virtual SDL_Rect* GetDestRect() const;
	virtual void SetSrcRect(SDL_Rect* src);
	virtual void SetDestRect(SDL_Rect* dest);
	virtual bool ContainsCoordinates(float x, float y) const;
private:
	//нужна непрерывность координат
	float x;
	float y;
	//прямоугольник, куда рисуется изображение
	SDL_Rect* destRect;
	//определяет, какую часть исходного изображения рисовать
	SDL_Rect* srcRect;
	//картинка
	SDL_Surface* image;
};

#endif /* DRAWABLE_DRAW_H_ */

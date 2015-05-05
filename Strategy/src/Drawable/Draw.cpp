/*
 * Draw.cpp
 *
 *  Created on: 11 апр. 2015 г.
 *      Author: ivanmatveev
 */

#include "Draw.h"

Draw::Draw(SDL_Rect src, const char *name_file_image, Uint8 transparency)
{
	destRect = new SDL_Rect(src);
	srcRect = new SDL_Rect(src);
	destRect->x = 0;
	destRect->y = 0;
	x = src.x;
	y = src.y;
	image = SDL_LoadBMP(name_file_image);
	if (!image) {
		std::string str("Draw cannot open image: ");
		str += name_file_image;
		throw(str);
	}
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format,255, 0, 255));
	SDL_SetAlpha(image,SDL_SRCALPHA, transparency);
}
Draw::~Draw()
{
	SDL_FreeSurface(image);
	delete(destRect);
	delete(srcRect);
}
SDL_Surface* Draw::GetImage() const {return image;}
void Draw::SetImage(SDL_Surface* Image){
	SDL_FreeSurface(image);
	image = Image;
 }

float Draw::GetX() const {return x;}

float Draw::GetY() const {return y;}

void Draw::SetX(float x) {
	this->x = x;
	destRect->x = static_cast<Sint16>(x);
}

void Draw::SetY(float y) {
	this->y = y;
	destRect->y = static_cast<Sint16>(y);
}

float Draw::GetWidth() const {return static_cast<float>(srcRect->w);}

float Draw::GetHeight() const {return static_cast<float>(srcRect->h);}

SDL_Rect* Draw::GetSrcRect() const { return srcRect;}

SDL_Rect* Draw::GetDestRect() const { return destRect;}

void Draw::SetSrcRect(SDL_Rect* src) {
	*srcRect = *src;
	destRect->w = srcRect->w;
	destRect->h = srcRect->h;
}
void Draw::SetDestRect(SDL_Rect* dest) {
	*destRect = *dest;
	x = static_cast<float>(destRect->x);
	y = static_cast<float>(destRect->y);
	srcRect->w = destRect->w;
	srcRect->h = destRect->h;
}

bool Draw::ContainsCoordinates(float x, float y) const {
	auto relativeX = x - destRect->x;
	auto relativeY = y - destRect->y;
	return (relativeX >=0 && relativeY >=0 &&
			relativeX <= srcRect->w && relativeY <= srcRect->h);
}






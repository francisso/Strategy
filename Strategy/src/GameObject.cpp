/*
 *
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "GameObject.h"

GameObject::GameObject(SDL_Rect src, const char *name_file_image) {
	destRect = new SDL_Rect(src);
	srcRect = new SDL_Rect(src);
	destRect->x = 0;
	destRect->y = 0;
	x = src.x;
	y = src.y;
	width = src.w;
	height = src.h;
	imageX = 0;
	imageY = 0;
	image = SDL_LoadBMP(name_file_image);

	if (!image)
		throw("GameObject cannot open image");
	//SDL_SetColorKey(image, SDL_SRCALPHA, 0x000000ff);
	if (!strcmp(name_file_image, "res/images/selection.bmp"))
		SDL_SetAlpha(image,SDL_SRCALPHA,150);
}

GameObject::~GameObject() {
	SDL_FreeSurface(image);
	delete(destRect);
	delete(srcRect);
}

void GameObject::Update(float time) {
	//TODO implement function
	time = 1.0f*time;
}

SDL_Surface* GameObject::GetImage() {return image;}

CoordinateType GameObject::GetX() {return x;}

CoordinateType GameObject::GetY() {return y;}

void GameObject::SetX(CoordinateType x) {
	this->x = x;
	destRect->x = static_cast<Sint16>(x);
}

void GameObject::SetY(CoordinateType y) {
	this->y = y;
	destRect->y = static_cast<Sint16>(y);
}

CoordinateType GameObject::GetWidth() {return width;}

CoordinateType GameObject::GetHeight() {return height;}

SDL_Rect* GameObject::GetSrcRect() { return destRect;}

SDL_Rect* GameObject::GetDestRect() { return srcRect;}


bool GameObject::ContainsCoordinates(float x, float y) {
	auto relativeX = x - this->x;
	auto relativeY = y - this->y;
	return (relativeX >=0 && relativeY >=0 &&
			relativeX <= width && relativeY <= height);
}

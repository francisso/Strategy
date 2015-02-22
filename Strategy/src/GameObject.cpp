/*
 /*
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "GameObject.h"

GameObject::GameObject(SDL_Rect *src, const char *name_file_image) {
	x = src->x;
	y = src->y;
	width = src->w;
	height = src->h;
	sx = 0;
	sy = 0;
	image = SDL_LoadBMP(name_file_image);
	if (!image) {
		std::cout << "Error: " << SDL_GetError() << "\n";
		return;
	}
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format,255, 0, 255));
}

GameObject::~GameObject() {
	SDL_FreeSurface(image);
}

void GameObject::Update(float time) {
	//TODO implement function

}

SDL_Surface* GameObject::GetImage() {
	return image;
}
CoordinateType GameObject::X() {return x;}

CoordinateType GameObject::Y() {return y;}

CoordinateType GameObject::GetWidth() {return width;}

CoordinateType GameObject::GetHeight() {return height;}

SDL_Rect* GameObject::GetSrcRect() {
	SDL_Rect src;
	src.x = sx;
	src.y = sy;
	src.w = width;
	src.h = height;
	return &src;
}
SDL_Rect* GameObject::GetDestRect() {
	SDL_Rect desc;
	desc.x = x;
	desc.y = y;
	desc.w = width;
	desc.h = height;
	return &desc;
}

bool GameObject::ContainsCoordinates(Uint16 x, Uint16 y) {
	auto relativeX = x - this->x;
	auto relativeY = y - this->y;
	return (relativeX >=0 && relativeY >=0 &&
			relativeX <= width && relativeY <= height);
}

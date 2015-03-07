/*
 *
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "GameObject.h"

GameObject::GameObject(SDL_Rect src, const char *name_file_image) {
	srcRect = new SDL_Rect(src);
	destRect = new SDL_Rect(src);
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
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format,255, 0, 255));
}

GameObject::~GameObject() {
	SDL_FreeSurface(image);
	delete(srcRect);
	delete(destRect);
}

void GameObject::Update(float time) {
	//TODO implement function
}

SDL_Surface* GameObject::GetImage() {
	return image;
}
/*
void GameObject::SetImage(SDL_Surface* Image) {
	image = Image;
}
*/
CoordinateType GameObject::X() {return x;}

CoordinateType GameObject::Y() {return y;}

void GameObject::setX(CoordinateType X) {
	x = X;
	srcRect->x = X;
#warning "Не destRect ли здесь нужно менять?"
}

void GameObject::setY(CoordinateType Y) {
	y = Y;
	srcRect->y = Y;
#warning "Не destRect ли здесь нужно менять?"
}

CoordinateType GameObject::GetWidth() {return width;}

CoordinateType GameObject::GetHeight() {return height;}

SDL_Rect* GameObject::GetSrcRect() { return srcRect;}

SDL_Rect* GameObject::GetDestRect() { return destRect;}


bool GameObject::ContainsCoordinates(Uint16 x, Uint16 y) {
	auto relativeX = x - this->x;
	auto relativeY = y - this->y;
	return (relativeX >=0 && relativeY >=0 &&
			relativeX <= width && relativeY <= height);
}

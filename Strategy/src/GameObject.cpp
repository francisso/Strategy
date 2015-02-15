/*
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "GameObject.h"

GameObject::GameObject() {
	// TODO Auto-generated constructor stub

}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}

void GameObject::Update(float time) {
	//TODO implement function

}

SDL_Surface* GameObject::GetImage() {
	//TODO implement function
	return nullptr;
}
CoordinateType GameObject::X() {return x;}

CoordinateType GameObject::Y() {return y;}

CoordinateType GameObject::GetWidth() {return width;}

CoordinateType GameObject::GetHeight() {return height;}

SDL_Rect* GameObject::GetSrcRect() {
	//TODO implement function
	return nullptr;
}
SDL_Rect* GameObject::GetDestRect() {
	//TODO implement function
	return nullptr;
}

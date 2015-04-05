/*
 *
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "GameObject.h"

GameObject::GameObject(SDL_Rect src, const char *name_file_image, GameObjectType type, float maxSpeed, unsigned int maxHP, int ownerID, Uint8 transparency):
		ObjectType(type),MaxSpeed(maxSpeed),MaxHP(maxHP),currentHP(maxHP),ownerID(ownerID) {
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
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format,255, 0, 255));
	SDL_SetAlpha(image,SDL_SRCALPHA,transparency);
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 *Переопределение методов View
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */
GameObject::~GameObject() {
	SDL_FreeSurface(image);
	delete(destRect);
	delete(srcRect);
}

void GameObject::Update(float time) {
	//TODO implement function
	time = 1.0f*time;
}


/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Реализация методов Drowable
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */
SDL_Surface* GameObject::GetImage() const {return image;}

CoordinateType GameObject::GetX() const {return x;}

CoordinateType GameObject::GetY() const {return y;}

void GameObject::SetX(CoordinateType x) {
	this->x = x;
	destRect->x = static_cast<Sint16>(x);
}

void GameObject::SetY(CoordinateType y) {
	this->y = y;
	destRect->y = static_cast<Sint16>(y);
}

CoordinateType GameObject::GetWidth() const {return width;}

CoordinateType GameObject::GetHeight() const {return height;}

SDL_Rect* GameObject::GetSrcRect() const { return srcRect;}

SDL_Rect* GameObject::GetDestRect() const { return destRect;}

void GameObject::SetSrcRect(SDL_Rect* src) {
	*srcRect = *src;
	imageX = srcRect->x;
	imageY = srcRect->y;
	width = srcRect->w;
	height = srcRect->h;
	destRect->w = srcRect->w;
	destRect->h = srcRect->h;
}
void GameObject::SetDestRect(SDL_Rect* dest) {
	*destRect = *dest;
	x = destRect->x;
	y = destRect->y;
	width = destRect->w;
	height = destRect->h;
	srcRect->w = destRect->w;
	srcRect->h = destRect->h;
}

bool GameObject::ContainsCoordinates(float x, float y) const {
	auto relativeX = x - this->x;
	auto relativeY = y - this->y;
	return (relativeX >=0 && relativeY >=0 &&
			relativeX <= width && relativeY <= height);
}


/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Реализация методов IGameObject
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

GameObjectType GameObject::GetObjectType(){return this->ObjectType;}

unsigned int GameObject::GetMaxHP(){return MaxHP;}

unsigned int GameObject::GetCurrHP(){return currentHP;}

void GameObject::DealDamage(int damage){
	unsigned int unsigned_damage;
	if(damage>=0){
		unsigned_damage=static_cast<unsigned int>(damage);
		if(unsigned_damage>currentHP){
			currentHP=0;
		} else {
			currentHP-=unsigned_damage;
		}
	} else {
		unsigned_damage=static_cast<unsigned int>(-damage);
		if(currentHP+unsigned_damage>MaxHP){
			currentHP=MaxHP;
		} else {
			currentHP+=unsigned_damage;
		}
	}
}

float GameObject::GetSpeed(){return MaxSpeed;}

int GameObject::GetOwnerID(){return ownerID;}

void GameObject::SetOwnerID(int ID){ownerID=ID;}

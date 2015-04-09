/*
 *
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "../GameObjects/PlayingObject.h"

PlayingObject::PlayingObject(SDL_Rect src, const char *name_file_image, GameObjectType type, float maxSpeed, unsigned int maxHP, int ownerID, Uint8 transparency):
		ObjectType(type),MaxSpeed(maxSpeed),MaxHP(maxHP),currentHP(maxHP),ownerID(ownerID),isPicked(false) {
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
PlayingObject::~PlayingObject() {
	SDL_FreeSurface(image);
	delete(destRect);
	delete(srcRect);
}

void PlayingObject::Update(float time) {
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
SDL_Surface* PlayingObject::GetImage() const {return image;}

CoordinateType PlayingObject::GetX() const {return x;}

CoordinateType PlayingObject::GetY() const {return y;}

void PlayingObject::SetX(CoordinateType x) {
	this->x = x;
	destRect->x = static_cast<Sint16>(x);
}

void PlayingObject::SetY(CoordinateType y) {
	this->y = y;
	destRect->y = static_cast<Sint16>(y);
}

CoordinateType PlayingObject::GetWidth() const {return width;}

CoordinateType PlayingObject::GetHeight() const {return height;}

SDL_Rect* PlayingObject::GetSrcRect() const { return srcRect;}

SDL_Rect* PlayingObject::GetDestRect() const { return destRect;}

void PlayingObject::SetSrcRect(SDL_Rect* src) {
	*srcRect = *src;
	imageX = srcRect->x;
	imageY = srcRect->y;
	width = srcRect->w;
	height = srcRect->h;
	destRect->w = srcRect->w;
	destRect->h = srcRect->h;
}
void PlayingObject::SetDestRect(SDL_Rect* dest) {
	*destRect = *dest;
	x = destRect->x;
	y = destRect->y;
	width = destRect->w;
	height = destRect->h;
	srcRect->w = destRect->w;
	srcRect->h = destRect->h;
}

bool PlayingObject::ContainsCoordinates(float x, float y) const {
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

GameObjectType PlayingObject::GetObjectType(){return this->ObjectType;}

unsigned int PlayingObject::GetMaxHP(){return MaxHP;}

unsigned int PlayingObject::GetCurrHP(){return currentHP;}

void PlayingObject::DealDamage(int damage){
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

float PlayingObject::GetSpeed(){return MaxSpeed;}

int PlayingObject::GetOwnerID(){return ownerID;}

void PlayingObject::SetOwnerID(int ID){ownerID=ID;}

bool PlayingObject::IsPicked(){return isPicked;}

void PlayingObject::SetPicked(bool isPicked){this->isPicked=isPicked;}

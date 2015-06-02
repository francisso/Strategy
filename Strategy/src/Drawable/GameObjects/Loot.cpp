/*
 * Loot.cpp
 *
 *  Created on: May 21, 2015
 *      Author: staslatgttt
 */

#include "Loot.h"

Loot::Loot(SDL_Rect src, const char* name_file_image, LootType type, int amount, Uint8 transparency):GameObject(src,name_file_image,LOOT,transparency),type(type),amount(amount){}

LootType Loot::WhatIs(){return this->type;}

int Loot::GetAmount(){return this->amount;}

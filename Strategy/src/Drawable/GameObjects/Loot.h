/*
 * Loot.h
 *
 *  Created on: Apr 9, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_LOOT_H_
#define DRAWABLE_GAMEOBJECTS_LOOT_H_

#include "../../Drawable/GameObject.h"

class Loot: public GameObject{
private:
	LootType type;
	int amount;
public:
	Loot(SDL_Rect src, char* name_file_image, LootType type, int amount, Uint8 transparency=255);
	LootType WhatIs();
	int GetAmount();
};

#endif /* DRAWABLE_GAMEOBJECTS_LOOT_H_ */

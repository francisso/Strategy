/*
 * GameObject.h
 *
 *  Created on: Apr 9, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECT_H_
#define DRAWABLE_GAMEOBJECT_H_

#include "Draw.h"

class GameObject: public Draw{
public:
	GameObject(SDL_Rect src, const char *name_file_image, GameObjectType type,
			Uint8 transparency = 255);
	~GameObject() = default;
	virtual GameObjectType GetObjectType();
private:
	const GameObjectType ObjectType;
};

#endif /* DRAWABLE_GAMEOBJECT_H_ */

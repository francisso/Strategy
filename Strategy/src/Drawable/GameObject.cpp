/*
 * GameObject.cpp
 *
 *  Created on: 11 апр. 2015 г.
 *      Author: ivanmatveev
 */

#include "GameObject.h"

GameObject::GameObject(SDL_Rect src, const char *name_file_image,GameObjectType type,
		Uint8 transparency):
		Draw(src, name_file_image, transparency),
		ObjectType(type)
{}

GameObjectType GameObject::GetObjectType() { return ObjectType;}



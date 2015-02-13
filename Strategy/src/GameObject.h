/*
 * GameObject.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Drawable.h"

class GameObject: public Drawable {
public:
	GameObject();
	virtual ~GameObject();
};

#endif /* GAMEOBJECT_H_ */

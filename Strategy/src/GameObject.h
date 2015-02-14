/*
 * GameObject.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Drawable.h"

//Базовый класс для юнитов, зданий, и т.д.
class GameObject: public Drawable {
public:
	GameObject();
	virtual ~GameObject();
	//Обновляет положение объекта на основе прошедшего времени
	virtual void UpdatePosition(float time);
};

#endif /* GAMEOBJECT_H_ */

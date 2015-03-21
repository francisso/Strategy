/*
 * Unit.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "../GameObject.h"
#include "Action.h"
#include "../Constants.h"
#include <cmath>
#include <queue>

class Unit : public GameObject{
public:
	virtual ~Unit()=default;
	Unit(SDL_Rect src, const char *name_file_image);
	struct Action* GetAction();
	void AddAction(struct Action* action, bool replace=true);
	void NextAction();
	float GetMaxSpeed();
	void SetX(CoordinateType x);
	void SetY(CoordinateType y);
	void SetVirtualX(float x);
	void SetVirtualY(float y);
	float GetVirtualX();
	float GetVirtualY();
	// TODO @stasltggg не ясно, что такое replace, нужны комментарии.
	void DirectMoveToCell(int x_target,int y_target,bool replace=true);
private:
	struct Action* action;
	std::queue<struct Action*> ActionQueue;
	// TODO @stasltggg Что это? Почему не константа?
	float MaxSpeed;
protected:
	// TODO @stasltggg добавить описание
	float VirtualX,VirtualY;
};

#endif /* UNIT_H_ */

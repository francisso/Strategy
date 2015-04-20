/*
 *
 * GameObject.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "../../Drawable/GameObjects/PlayingObject.h"

PlayingObject::PlayingObject(SDL_Rect src, const char *name_file_image,
							GameObjectType type, float maxSpeed, unsigned int maxHP,
							int ownerID, Uint8 transparency):
		GameObject(src, name_file_image, type, transparency),
		MaxSpeed(maxSpeed),
		MaxHP(maxHP),
		currentHP(maxHP),
		ownerID(ownerID),
		isPicked(false),
		destX(GetX()),
		destY(GetY()),
		currAction(Action::CreateMoveAction(WAIT)){}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 *Переопределение методов View
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

void PlayingObject::Update(float time) {
	//TODO implement function
	time = 1.0f*time;
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Реализация методов IPlayingObject
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

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

float PlayingObject::GetMaxSpeed(){return MaxSpeed;}

int PlayingObject::GetOwnerID(){return ownerID;}

void PlayingObject::SetOwnerID(int ID){ownerID=ID;}

bool PlayingObject::IsPicked(){return isPicked;}

void PlayingObject::SetPicked(bool isPicked){this->isPicked=isPicked;}

void PlayingObject::SetDestX(float destX){this->destX=destX;}

void PlayingObject::SetDestY(float destY){this->destY=destY;}

float PlayingObject::GetDestX(){return destX;}

float PlayingObject::GetDestY(){return destY;}

Action* PlayingObject::GetAction(){return currAction;}

void PlayingObject::AddAction(Action* action,bool replace)
{
	if (replace){
		while(!ActionQueue.empty())
			ActionQueue.pop();
	}
	ActionQueue.push(action);
	std::cout<<"actionType="<<action->type<<"; moveDir="<<action->moveDir<<std::endl;
}

void PlayingObject::NextAction(){
	if(this->ActionQueue.size()==0){
		this->currAction=Action::CreateMoveAction(WAIT);
	} else {
		this->currAction=this->ActionQueue.front();
		this->ActionQueue.pop();
	}
}

void PlayingObject::StopNow(){
	if(static_cast<int>(GetX())%CELL_X_PIXELS==0 && static_cast<int>(GetY())%CELL_Y_PIXELS==0)
	{
		while(!ActionQueue.empty())
			ActionQueue.pop();
		currAction=Action::CreateMoveAction(WAIT);
		}
}

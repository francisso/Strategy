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
	//std::cout<<std::endl<<std::endl<<std::endl;
	//std::cout<<"ActionQueue.size()="<<ActionQueue.size()<<std::endl;
	Action* temp;
	if (replace){
		while(!ActionQueue.empty()){
			temp=ActionQueue.front();
			delete(temp);
			ActionQueue.pop();
		}
	}
	//std::cout<<"ActionQueue.size()="<<ActionQueue.size()<<std::endl;
	ActionQueue.push(action);
	/*std::cout<<"ActionQueue.size()="<<ActionQueue.size()<<std::endl;
	Action* act = ActionQueue.front();
	std::cout<<"Current action: actionType="<<currAction->type<<"; current moveDir="<<currAction->moveDir<<std::endl;
	std::cout<<"Action to add: actionType="<<action->type<<"; moveDir="<<action->moveDir<<std::endl;
	std::cout<<"First action: actionType="<<act->type<<"; moveDir="<<act->moveDir<<std::endl;
	std::cout<<"action="<<action<<"; act="<<act<<std::endl;
	std::cout<<std::endl<<std::endl<<std::endl;*/
}

void PlayingObject::NextAction(){
	Action* temp=currAction;
	delete(temp);
	if(this->ActionQueue.empty()){
		this->currAction=Action::CreateMoveAction(WAIT);
	} else {
		this->currAction=this->ActionQueue.front();
		this->ActionQueue.pop();
	}
}

void PlayingObject::Stop(){
	Action* temp;
	while(!ActionQueue.empty())
	{
		temp=ActionQueue.front();
		delete(temp);
		ActionQueue.pop();
	}
}

void PlayingObject::RepeatLastAction(){
	ActionQueue.push(currAction);
	long unsigned int n=ActionQueue.size();
	for(long unsigned int i=0;i<n;i++)
	{
		ActionQueue.push(ActionQueue.front());
		ActionQueue.pop();
	}
}

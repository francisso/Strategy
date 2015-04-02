/*
 * Unit.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "Unit.h"
#include <iostream>

Unit::Unit(SDL_Rect src, const char *name_file_image) : GameObject(src, name_file_image),MaxSpeed(2) {
	//TODO this initialization is a developer version
	auto action = new Action();
	action->type=STAY;
	action->who = this;
	this->action = action;
	this->DestinationX=this->GetX();
	this->DestinationY=this->GetY();
	//std::cout<<DestinationX<<"=VirtualX=GetX()="<<GetX()<<std::endl;
}

Action* Unit::GetAction() const {
	return action;
}

float Unit::GetMaxSpeed() const{
	return MaxSpeed;
}

/*void Unit::SetAction(Action* action) {
	this->action = action;
}*/

void Unit::AddAction(Action* action, bool replace){
	if (replace){
		while(!ActionQueue.empty())
			ActionQueue.pop();
		ActionQueue.push(action);
	} else {
		ActionQueue.push(action);
	}
	// TODO если это нужно, то надо то дебаг вывод нужно делать через ifdef DEBUG...
	//std::cout<<"AddAction(): ActionQueue.size="<<ActionQueue.size()<<std::endl;
}

void Unit::NextAction() {
	if(this->ActionQueue.size()==0){
		this->action->type=STAY;
		//std::cout<<"NextAction(): size==0"<<std::endl;
	} else {
		this->action=this->ActionQueue.front();
		this->ActionQueue.pop();
		//std::cout<<"NextAction(): size!=0"<<std::endl;
	}
	// TODO если это нужно, то надо то дебаг вывод нужно делать через ifdef DEBUG...
	//std::cout<<"NextAction(): ActionQueue.size="<<ActionQueue.size()<<std::endl;
}

void Unit::SetDestinationX(float x){this->DestinationX=x;}

void Unit::SetDestinationY(float y){this->DestinationY=y;}

float Unit::GetDestinationX() const {return this->DestinationX;}

float Unit::GetDestinationY() const {return this->DestinationY;}

void Unit::DirectMoveToCell(int x_target,int y_target,bool replace){
	int x_start=static_cast<int>(this->GetDestinationX()/CELL_X_PIXELS);
	int y_start=static_cast<int>(this->GetDestinationY()/CELL_Y_PIXELS);
	std::cout<<"x_target="<<x_target<<" ;y_target="<<y_target<<" ;x_start="<<x_start<<" ;y_start="<<y_start<<std::endl;
	int x_range=x_target-x_start;
	int y_range=y_target-y_start;
	std::cout<<"x_range="<<x_range<<"; y_range="<<y_range<<std::endl;
	if(replace){
		this->AddAction(Action::CreateAction(STAY,false));
	}
	while(x_range!=0 || y_range!=0){
		if (std::abs(x_range)>std::abs(y_range)){
			if(x_range>0){
				this->AddAction(Action::CreateAction(MOVE_HORIZONTAL,true),false);
				x_range--;
			} else {
				this->AddAction(Action::CreateAction(MOVE_HORIZONTAL,false),false);
				x_range++;
			}
		} else {
			if(y_range>0){
				this->AddAction(Action::CreateAction(MOVE_VERTICAL,true),false);
				y_range--;
			} else {
				this->AddAction(Action::CreateAction(MOVE_VERTICAL,false),false);
				y_range++;
			}
		}
	}
	this->SetDestinationX(static_cast<float>(x_target*CELL_X_PIXELS));
	this->SetDestinationY(static_cast<float>(y_target*CELL_Y_PIXELS));
}

void Unit::SetX(CoordinateType x){
	GameObject::SetX(x);
	this->DestinationX=x;
}

void Unit::SetY(CoordinateType y){
	GameObject::SetY(y);
	this->DestinationY=y;
}

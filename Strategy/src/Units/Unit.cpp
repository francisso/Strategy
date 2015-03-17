/*
 * Unit.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "Unit.h"

Unit::Unit(SDL_Rect src, const char *name_file_image) : GameObject(src, name_file_image) {
	//TODO this initialization is a developer version
	auto action = new Action();
	action->actionType= Action::STAY;
	action->who = this;
	this->action = action;
	this->MaxSpeed=1.0f;
}

Action* Unit::GetAction() {
	return action;
}

float Unit::GetMaxSpeed(){
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
	//std::cout<<"AddAction(): ActionQueue.size="<<ActionQueue.size()<<std::endl;
}

void Unit::NextAction(){
	if(this->ActionQueue.size()==0){
		this->action->actionType=Action::STAY;
		//std::cout<<"NextAction(): size==0"<<std::endl;
	} else {
		this->action=this->ActionQueue.front();
		this->ActionQueue.pop();
		//std::cout<<"NextAction(): size!=0"<<std::endl;
	}
	//std::cout<<"NextAction(): ActionQueue.size="<<ActionQueue.size()<<std::endl;
}

void Unit::MoveToCell(int x_target,int y_target,bool replace){
	int x_start=(int)(this->GetX()/CELL_X_PIXELS);
	int y_start=(int)(this->GetY()/CELL_Y_PIXELS);
	int x_range=x_target-x_start;
	int y_range=y_target-y_start;
	if(replace){
		this->AddAction(Stay());
	}
	while(x_range!=0 || y_range!=0){
		if (std::abs(x_range)>std::abs(y_range)){
			if(x_range>0){
				this->AddAction(MoveRight(),false);
				x_range--;
			} else {
				this->AddAction(MoveLeft(),false);
				x_range++;
			}
		} else {
			if(y_range>0){
				this->AddAction(MoveDown(),false);
				y_range--;
			} else {
				this->AddAction(MoveUp(),false);
				y_range++;
			}
		}
	}
}

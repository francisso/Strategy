/*
 * Unit.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "../../../Drawable/GameObjects/Units/Unit.h"
#include <iostream>

Unit::Unit(SDL_Rect src, const char *name_file_image,float maxSpeed,unsigned int maxHP,int ownerID): PlayingObject(src, name_file_image,UNIT,maxSpeed,maxHP,ownerID),Rotating(4) {}

inline int sign(int temp){
	return (temp>0)?1:-1;
}

void Unit::DirectMoveToCell(int x_target,int y_target,bool replace){
	if(replace){
		Stop();
	}
	int x_curr=(static_cast<int>(GetDestX()))/CELL_X_PIXELS;
	int y_curr=(static_cast<int>(GetDestY()))/CELL_Y_PIXELS;
	int x_range=x_target-x_curr;
	int y_range=y_target-y_curr;
	std::cout<<"x_range="<<x_range<<"; y_range="<<y_range<<std::endl;
	Direction dir;
	if(abs(x_range)>abs(y_range)){
		if(x_range>0) dir=EAST;
		else dir=WEST;
		while(abs(x_range)>abs(y_range)){
			AddAction(Action::CreateMoveAction(MOVE,dir),false);
			x_range=x_range-sign(x_range);
		}
	} else if (abs(y_range)>abs(x_range)){
		if(y_range>0) dir=SOUTH;
		else dir=NORTH;
		while(abs(x_range)<abs(y_range)){
			AddAction(Action::CreateMoveAction(MOVE,dir),false);
			y_range=y_range-sign(y_range);
		}
	}
	dir=Rotating::Arctan(x_range,y_range);
	while(abs(x_range)>0){
		AddAction(Action::CreateMoveAction(MOVE,dir),false);
		x_range=x_range-sign(x_range);
		y_range=y_range-sign(y_range);
	}
	SetDestX(static_cast<float>(CELL_X_PIXELS*x_range));
	SetDestY(static_cast<float>(CELL_Y_PIXELS*y_range));
}

void Unit::Stop(){
	while(!ActionQueue.empty()){
		ActionQueue.pop();
	}
	if(static_cast<int>(GetX())%CELL_X_PIXELS==0 && static_cast<int>(GetY())%CELL_Y_PIXELS==0){
		currAction=Action::CreateMoveAction(WAIT);
		return;
	}

	if(NextCellDirX()<0)
	{
		SetDestX(static_cast<float>((static_cast<int>(GetX())%CELL_X_PIXELS-1)*CELL_X_PIXELS));
	}else{
		SetDestX(static_cast<float>((static_cast<int>(GetX())%CELL_X_PIXELS)*CELL_X_PIXELS));
	}

	if(NextCellDirY()>0)
	{
		SetDestY(static_cast<float>((static_cast<int>(GetY())%CELL_Y_PIXELS+1)*CELL_Y_PIXELS));
	}else{
		SetDestY(static_cast<float>((static_cast<int>(GetY())%CELL_Y_PIXELS)*CELL_Y_PIXELS));
	}
}

void Unit::SetX(float x){
	PlayingObject::SetX(x);
	//SetDestX(x);
}

void Unit::SetY(float y){
	PlayingObject::SetY(y);
	//SetDestY(y);
}

float Unit::GetXSpeed(){
	return this->GetMaxSpeed()*Rotating::SpeedModifierX(this->GetDirection());
}

float Unit::GetYSpeed(){
	return this->GetMaxSpeed()*Rotating::SpeedModifierY(this->GetDirection());
}

int Unit::NextCellDirX(){
	return Rotating::NextCellX(this->GetDirection());
}

int Unit::NextCellDirY(){
	return Rotating::NextCellY(this->GetDirection());
}

void Unit::NextAction(){
	PlayingObject::NextAction();
	this->SetAngle(GetAction()->moveDir);
}

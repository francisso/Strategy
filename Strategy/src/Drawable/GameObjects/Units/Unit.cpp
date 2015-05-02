/*
 * Unit.cpp
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#include "../../../Drawable/GameObjects/Units/Unit.h"
#include <iostream>

Unit::Unit(SDL_Rect src, const char *name_file_image, UnitType unitType, float maxSpeed,unsigned int maxHP,int ownerID): PlayingObject(src, name_file_image,UNIT,maxSpeed,maxHP,ownerID),Rotating(4),whoIs(unitType),triesLeft(NUMBER_OF_TRIES) {}

inline int sign(int temp){
	return (temp>0)?1:-1;
}

void Unit::DirectMoveToCell(int x_target,int y_target,bool replace){
	if(replace){
		this->Stop();
	}
	int x_curr=(static_cast<int>(GetDestX()))/CELL_X_PIXELS;
	int y_curr=(static_cast<int>(GetDestY()))/CELL_Y_PIXELS;
	std::cout<<"x_curr="<<x_curr<<"; y_curr="<<y_curr<<std::endl;
	int x_range=x_target-x_curr;
	int y_range=y_target-y_curr;
	std::cout<<"x_curr="<<x_curr<<"; y_curr="<<y_curr<<"; x_target="<<x_target<<"; y_target="<<y_target<<"; x_range="<<x_range<<"; y_range="<<y_range<<std::endl;
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
	SetDestX(static_cast<float>(CELL_X_PIXELS*x_target));
	SetDestY(static_cast<float>(CELL_Y_PIXELS*y_target));
	//std::cout<<"x_curr="<<x_curr<<"; y_curr="<<y_curr<<"; x_target="<<x_target<<"; x_target="<<x_target<<"; x_range="<<x_range<<"; y_range="<<y_range<<std::endl;
}

void Unit::Stop(){
	PlayingObject::Stop();
	float CELL_X=static_cast<float>(CELL_X_PIXELS);
	float CELL_Y=static_cast<float>(CELL_Y_PIXELS);

	if(currAction->type==WAIT) return;

	if(this->NextCellDirY()>0){
		SetDestY(CELL_Y*static_cast<float>(static_cast<int>(GetY()/CELL_Y)+1));
	} else if (this->NextCellDirY()<0){
		SetDestY(CELL_Y*static_cast<float>(static_cast<int>(GetY()/CELL_Y)));
	} else if (this->NextCellDirY()==0){
		SetDestY(GetY());
	}

	if(this->NextCellDirX()>0){
			SetDestX(CELL_X*static_cast<float>(static_cast<int>(GetX()/CELL_X)+1));
		} else if (this->NextCellDirX()<0){
			SetDestX(CELL_X*static_cast<float>(static_cast<int>(GetX()/CELL_X)));
		} else if (this->NextCellDirX()==0){
			SetDestX(GetX());
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

UnitType Unit::WhoIs(){return whoIs;}

void Unit::ReduceTries(){triesLeft--;}

void Unit::RestoreTries(){triesLeft=NUMBER_OF_TRIES;}

int Unit::GetTries(){return triesLeft;}

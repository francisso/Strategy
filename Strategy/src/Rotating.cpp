/*
 * Angle.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: staslatgttt
 */

#include "Rotating.h"

Rotating::Rotating(int ang){
	while(ang<0){
		ang+=8;
	}
	ang=ang%8;
	this->angle=static_cast<Direction>(ang);
}

Rotating::Rotating(Direction newDir): angle(newDir){

}

Rotating::Rotating(Rotating* newAngle): angle(newAngle->GetDirection()){

}

Direction Rotating::GetDirection(){
	return this->angle;
}

void Rotating::SetAngle(int ang){
	while(ang<0){
		ang+=8;
	}
	ang=ang%8;
	this->angle=static_cast<Direction>(ang);
}

void Rotating::SetAngle(Direction newDir){
	this->angle=newDir;
}

void Rotating::SetAngle(Rotating* newAngle){
	this->angle=newAngle->GetDirection();
}

void Rotating::TurnRight(int ang){
	while(ang<0){
		ang+=8;
	}
	this->angle=static_cast<Direction>((this->angle+ang)%8);
}

void Rotating::TurnLeft(int ang){
	while((8-ang)<0){
		ang-=8;
	}
	this->angle=static_cast<Direction>((this->angle+(8-ang))%8);
}

Direction Rotating::Arctan(float delta_x,float delta_y){
	float x=delta_x,y=delta_y,tan;
	if(x!=0){
		tan=y/x;
		if(x>0){
			if(tan>=tanPi3of8){
				return SOUTH;
			}
			if(tan>=tanPi1of8){
				return SOUTH_EAST;
			}
			if(tan>=(-tanPi1of8)){
				return EAST;
			}
			if(tan>=(-tanPi3of8)){
				return NORTH_EAST;
			}
			return NORTH;
		} else {
			if(tan<=(-tanPi3of8)){
				return SOUTH;
			}
			if(tan<=(-tanPi1of8)){
				return SOUTH_WEST;
			}
			if(tan<=tanPi1of8){
				return WEST;
			}
			if(tan<=tanPi3of8){
				return NORTH_WEST;
			}
			return NORTH;
		}
	} else {
		if(y>0) return SOUTH;
		else return NORTH;
	}
}

Direction Rotating::Arctan(int delta_x, int delta_y){
	float x=static_cast<float>(delta_x),y=static_cast<float>(delta_y);
	return Arctan(x,y);
}

int Rotating::GetDifference(Direction dir1,Direction dir2){
	int temp=dir1-dir2;
	while(temp<-4){
		temp+=8;
	}
	while(temp>4){
		temp-=8;
	}
	return temp;
}

int Rotating::GetDifference(Direction dir,Rotating* rot){
	return GetDifference(dir,rot->GetDirection());
}

int Rotating::GetDifference(Rotating* rot1,Rotating* rot2){
	return GetDifference(rot1->GetDirection(),rot2->GetDirection());
}

int Rotating::GetDifference(Rotating* rot,Direction dir){
	return GetDifference(rot->GetDirection(),dir);
}

float Rotating::SpeedModifierX(Direction dir){
	switch(dir)
	{
	case NORTH:
		return 0.0;
	case NORTH_EAST:
		return sqrtOneSecond;
	case EAST:
		return 1.0;
	case SOUTH_EAST:
		return sqrtOneSecond;
	case SOUTH:
		return 0.0;
	case SOUTH_WEST:
		return -sqrtOneSecond;
	case WEST:
		return -1.0;
	case NORTH_WEST:
		return -sqrtOneSecond;
	}
	return 0.0;
}

float Rotating::SpeedModifierY(Direction dir){
	switch(dir)
	{
	case NORTH:
		return -1.0;
	case NORTH_EAST:
		return -sqrtOneSecond;
	case EAST:
		return 0.0;
	case SOUTH_EAST:
		return sqrtOneSecond;
	case SOUTH:
		return 1.0;
	case SOUTH_WEST:
		return sqrtOneSecond;
	case WEST:
		return 0.0;
	case NORTH_WEST:
		return -sqrtOneSecond;
	}
	return 0.0;
}

int Rotating::NextCellX(Direction dir){
	switch(dir)
	{
	case NORTH:
		return 0;
	case NORTH_EAST:
		return 1;
	case EAST:
		return 1;
	case SOUTH_EAST:
		return 1;
	case SOUTH:
		return 0;
	case SOUTH_WEST:
		return -1;
	case WEST:
		return -1;
	case NORTH_WEST:
		return -1;
	}
	return 0;
}

int Rotating::NextCellY(Direction dir){
	switch(dir)
	{
	case NORTH:
		return -1;
	case NORTH_EAST:
		return -1;
	case EAST:
		return 0;
	case SOUTH_EAST:
		return 1;
	case SOUTH:
		return 1;
	case SOUTH_WEST:
		return 1;
	case WEST:
		return 0;
	case NORTH_WEST:
		return -1;
	}
	return 0;
}

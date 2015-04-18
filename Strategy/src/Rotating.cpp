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

Rotating::Rotating(Rotating* newAngle): angle(newAngle->GetAngle()){

}

Direction Rotating::GetAngle(){
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
	this->angle=newAngle->GetAngle();
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
				return DOWN;
			}
			if(tan>=tanPi1of8){
				return DOWN_RIGHT;
			}
			if(tan>=(-tanPi1of8)){
				return RIGHT;
			}
			if(tan>=(-tanPi3of8)){
				return UP_RIGHT;
			}
			return UP;
		} else {
			if(tan<=(-tanPi3of8)){
				return DOWN;
			}
			if(tan<=(-tanPi1of8)){
				return DOWN_LEFT;
			}
			if(tan<=tanPi1of8){
				return LEFT;
			}
			if(tan<=tanPi3of8){
				return UP_LEFT;
			}
			return UP;
		}
	} else {
		if(y>0) return DOWN;
		else return UP;
	}
}

Direction Rotating::Arctan(int delta_x, int delta_y){
	float x=static_cast<float>(delta_x),y=static_cast<float>(delta_y),tan;
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
	return GetDifference(dir,rot->GetAngle());
}

int Rotating::GetDifference(Rotating* rot1,Rotating* rot2){
	return GetDifference(rot1->GetAngle(),rot2->GetAngle());
}

int Rotating::GetDifference(Rotating* rot,Direction dir){
	return GetDifference(rot->GetAngle(),dir);
}

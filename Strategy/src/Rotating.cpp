/*
 * Angle.cpp
 *
 *  Created on: Apr 16, 2015
 *      Author: staslatgttt
 */

#include "Rotating.h"

Rotating::Rotating(Direction newDir): angle(newDir){

}

Rotating::Rotating(Rotating* newAngle): angle(newAngle->GetAngle()){

}

Direction Rotating::GetAngle(){
	return this->angle;
}

void Rotating::SetAngle(Direction newDir){
	this->angle=newDir;
}

void Rotating::SetAngle(Rotating* newAngle){
	this->angle=newAngle->GetAngle();
}

void Rotating::TurnRight(){
	this->angle=static_cast<Direction>((this->angle+1)%8);
}

void Rotating::TurnLeft(){
	this->angle=static_cast<Direction>((this->angle+7)%8);
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

/*
 * Player.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#include "Player.h"

Player::Player(int ID):PlayerID(ID),Gold(GOLD_DEFAULT){}

int Player::AddGold(int	income){
	if(Gold+income>=0){
		Gold-=income;
		return 0;
	} else return 1;
}

int Player::GetGold(){
	return Gold;
}

void Player::AddPickedUnit(Unit* unit, bool replace){
	if(replace){
		while(!chosenUnits.empty()){
			chosenUnits.pop_back();
		}
	}
	chosenUnits.push_back(unit);
}

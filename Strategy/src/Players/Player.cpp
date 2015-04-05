/*
 * Player.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#include "Player.h"

Player::Player(int ID,Color playerColor):PlayerID(ID),playerGold(GOLD_DEFAULT),playerColor(playerColor),task(NOTHING_TO_DO){
	this->playerSignature="Player "+PlayerID;
	std::cout<<"Created player ID:"<<PlayerID<<"-\""<<playerSignature<<"\""<<std::endl;
}

void Player::OnEvent(EventForPlayer* eventInfo){
	if (eventInfo == nullptr)
		return;
}

int Player::AddGold(int	income){
	if(playerGold+income>=0){
		playerGold-=income;
		return 0;
	} else return 1;
}

int Player::GetGold(){
	return playerGold;
}

void Player::AddPickedUnit(Unit* unit, bool replace){
	if(replace){
		while(!chosenUnits.empty()){
			chosenUnits.pop_back();
		}
	}
	chosenUnits.push_back(unit);
}

void Player::SetColor(Color newColor){
	this->playerColor=newColor;
}

void Player::SetSignature(std::string newSig){
	std::cout<<"Player ID:"<<PlayerID<<"-\""<<playerSignature<<"\" renamed to ";
	this->playerSignature=newSig;
	std::cout<<"ID:"<<PlayerID<<"-\""<<playerSignature<<"\""<<std::endl;
}

Color Player::GetColor(){
	return this->playerColor;
}

std::string Player::GetSignature(){
	return this->playerSignature;
}

std::string ColorToString(Color color){
	switch(color){
	case GREY:
		return "grey ";
	case RED:
		return "red ";
	case BLUE:
		return "blue ";
	case GREEN:
		return "green ";
	case YELLOW:
		return "yellow ";
	case CYAN:
		return "cyan ";
	case ORANGE:
		return "orange ";
	case PURPLE:
		return "purple ";
	case BROWN:
		return "brown ";
	default:
		return "<undefined color>";
	}
}

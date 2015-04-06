/*
 * Player.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#include "Player.h"

Player::Player(int ID,Color playerColor):PlayerID(ID),playerGold(GOLD_DEFAULT),playerColor(playerColor)/*,ShiftPressed(false)*/{
	this->playerSignature="";
	this->playerSignature.append("Player ");
	this->playerSignature.append(std::to_string(PlayerID));
	std::cout<<"Created player ID:"<<PlayerID<<"-\""<<playerSignature<<"\""<<std::endl;
}

/*TaskForGame Player::OnEvent(EventForPlayer* eventInfo){

}*/

int Player::AddGold(int	income){
	if(playerGold+income>=0){
		playerGold-=income;
		return 0;
	} else return 1;
}

int Player::GetGold(){
	return playerGold;
}

void Player::AddPickedObject(GameObject* object, bool replace){
	if(replace){
		while(!pickedObjects.empty()){
			GameObject* object=pickedObjects.back();
			object->SetPicked(false);
			pickedObjects.pop_back();
		}
	}
	if(object->IsPicked()) return;
	else object->SetPicked(true);
	pickedObjects.push_back(object);
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

GameObject* Player::GetPicked(unsigned int number){
	if(number>pickedObjects.size()){
		return nullptr;
	} else {
		return pickedObjects[number];
	}
}

unsigned int Player::GetPickedNumber(){
	return static_cast<unsigned int>(pickedObjects.size());
}

void Player::FreePickedObjects(){
	//std::cout<<"Number of picked is "<<pickedObjects.size()<<std::endl;
	while(pickedObjects.size()>0u){
		GameObject* object=pickedObjects.back();
		object->SetPicked(false);
		pickedObjects.pop_back();
	}
	//std::cout<<"Number of picked is "<<pickedObjects.size()<<std::endl;
}

//bool Player::IsShiftPressed(){return ShiftPressed;}

//void Player::SetShiftPressed(bool IsPressed){ShiftPressed=IsPressed};

std::string ColorToString(Color color){
	switch(color){
	case GREY:
		return "grey";
	case RED:
		return "red";
	case BLUE:
		return "blue";
	case GREEN:
		return "green";
	case YELLOW:
		return "yellow";
	case CYAN:
		return "cyan";
	case ORANGE:
		return "orange";
	case PURPLE:
		return "purple";
	case BROWN:
		return "brown";
	default:
		return "<undefined color>";
	}
}

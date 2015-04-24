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
	SDL_Rect src = {0, 0, CELL_X_PIXELS, CELL_Y_PIXELS};
	selection = new Draw(src, "res/images/playerSelection.bmp", 150);
	std::cout<<"Created player ID:"<<PlayerID<<"-\""<<playerSignature<<"\""<<std::endl;
}

Player::~Player(){
	delete selection;
}
/*TaskForGame Player::OnEvent(EventForPlayer* eventInfo){

}*/
void Player::DrawToScreen(std::function<void (Drawable*, float X0, float Y0)> f,
		float deltaX, float deltaY) const
{
	std::vector<PlayingObject*>::const_iterator it = pickedObjects.begin();
	for (; it != pickedObjects.end(); it++)
	{
		selection->SetX((*it)->GetX());
		selection->SetY((*it)->GetY());
		f(selection, deltaX, deltaY);
	}
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

void Player::AddPickedObject(PlayingObject* object, bool replace){
	if(replace){
		while(!pickedObjects.empty()){
			PlayingObject* object=pickedObjects.back();
			object->SetPicked(false);
			pickedObjects.pop_back();
		}
	} else {
		if(object->GetObjectType()==BUILDING && !pickedObjects.empty()){
			return;
		}
		if(object->GetObjectType()==UNIT){
			for(unsigned int i=0u;i<pickedObjects.size();i++){
				if(pickedObjects[i]->GetObjectType()==BUILDING)
					return;
			}
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

PlayingObject* Player::GetPicked(unsigned int number){
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
		PlayingObject* object=pickedObjects.back();
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

/*
 * Player.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#include "Player.h"

Player::Player(int ID,Color playerColor):PlayerID(ID),
										playerGold(GOLD_DEFAULT),
										playerColor(playerColor),
										building(nullptr)
										/*,ShiftPressed(false)*/
{
	this->playerSignature="";
	this->playerSignature.append("Player ");
	this->playerSignature.append(std::to_string(PlayerID));
	SDL_Rect src = {0, 0, CELL_X_PIXELS, CELL_Y_PIXELS};
	selection = new Draw(src, "res/images/gameplay/playerSelection.bmp", 150);
	std::cout<<"Created player ID:"<<PlayerID<<"-\""<<playerSignature<<"\""<<std::endl;
	SDL_Rect src1 = {0, 0, 4*CELL_X_PIXELS, 4*CELL_Y_PIXELS};
	selectionBuilding = new Draw(src1, "res/images/gameplay/selectionBuilding.bmp", 150);
	std::cout<<"Created player ID:"<<PlayerID<<"-\""<<playerSignature<<"\""<<std::endl;
	SDL_Rect h_src = {0, 0, 40, 7};
	char file_image[150];
	for (int i = 0; i < 4; i++){
		sprintf(file_image, "res/images/gameplay/health_%d.bmp", i);
		health[i] = new Draw(h_src, file_image);
	}
}

Player::~Player(){
	delete selection;
	delete selectionBuilding;
	for(int i = 0; i < 4; i++)
		delete health[i];
}
/*TaskForGame Player::OnEvent(EventForPlayer* eventInfo){

}*/
void Player::DrawToScreen(std::function<void (Drawable*, float X0, float Y0)> f,
		float deltaX, float deltaY) const
{
	std::vector<PlayingObject*>::const_iterator it = pickedObjects.begin();
	for (; it != pickedObjects.end(); it++)
	{
		if ((*it)->GetObjectType() == UNIT){
			unsigned int hp = (4*(*it)->GetCurrHP())/(*it)->GetMaxHP() - 1;
			health[hp]->SetX((*it)->GetX());
			health[hp]->SetY((*it)->GetY() + CELL_Y_PIXELS - 7);
			f(health[hp], deltaX, deltaY);
			selection->SetX((*it)->GetX());
			selection->SetY((*it)->GetY());
			f(selection, deltaX, deltaY);
		} else
		if ((*it)->GetObjectType() == BUILDING){
			selectionBuilding->SetX((*it)->GetX());
			selectionBuilding->SetY((*it)->GetY());
			f(selectionBuilding, deltaX, deltaY);
		}
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

void Player::UpdateStatusBar_selected(){
	Order order = {STATUS_BAR_AMOUNT, SELECTED, &counter, counter};
	list_of_orders.push_back(order);
	order.receiver = STATUS_BAR_ACTION;
	if (counter.size() > 0 && counter[0].object_type == BUILDING)
		order.data = building;
	list_of_orders.push_back(order);
}

void Player::AddPickedObject(PlayingObject* object, bool replace){
	if(replace){
		while(!pickedObjects.empty()){
			PlayingObject* object=pickedObjects.back();
			object->SetPicked(false);
			pickedObjects.pop_back();
		}
		counter.clear();
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
	if (object->GetObjectType() == BUILDING) {
		building = dynamic_cast<Building*>(object);
		counter.clear();
		AmountOfUnit amount;
		amount.object_type = BUILDING;
		amount.amount = 1;
		counter.push_back(amount);
	}
	else if (object->GetObjectType() == UNIT) {
		Unit* unit = dynamic_cast<Unit*>(object);
		bool flag = true;
		auto it = counter.begin();
		for ( ; it != counter.end(); it++)
			if (it->unit_type == unit->WhoIs()){
				it->amount++;
				flag = false;
				break;
			}
		if (flag) {
			auto amount = new AmountOfUnit;
			amount->object_type = UNIT;
			amount->unit_type = unit->WhoIs();
			amount->amount = 1;
			counter.push_back(*amount);
			delete amount;
		}
	}
	UpdateStatusBar_selected();
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
	counter.clear();
	UpdateStatusBar_selected();
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

/*
 * HumanPlayer.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: staslatgttt
 */

#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int ID,Color color,std::string signature):Player(ID,color){
	SetSignature(signature);
	std::cout<<"Created "<<ColorToString(playerColor)<<" with name \""<<GetSignature()<<"\""<<std::endl;
}


TaskForGame HumanPlayer::OnEvent(EventForPlayer* eventInfo){
	if(eventInfo->event->button.button==SDL_BUTTON_LEFT){
		//std::cout<<"Before returning PICK_OBJECT"<<std::endl;
		return PICK_OBJECT;
	}
	if(eventInfo->event->button.button==SDL_BUTTON_RIGHT){
		//std::cout<<"Before returning MOVE_PICKED_TO"<<std::endl;
		return MOVE_PICKED_TO;
	}
	return NOTHING_TO_DO;
}

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


void HumanPlayer::OnEvent(EventForPlayer* event){
	if (event == nullptr)
		return;
}

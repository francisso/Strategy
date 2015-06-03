/*
 * AI.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: staslatgttt
 */

#include "./AI.h"

AI::AI(int ID,Color color,std::string signature,AIMode mode): Player(ID,COMPUTER,color),Mode(mode){
	SetSignature(signature);
	std::cout<<"Created "<<ColorToString(playerColor)<<" ";
	switch(mode){
	case NEUTRAL:
		std::cout<<"Neutral ";
		break;
	case USUAL:
		std::cout<<"Usual ";
		break;
	}
	std::cout<<"AI with name \""<<GetSignature()<<"\""<<std::endl;
}


TaskForGame AI::OnEvent(EventForPlayer* eventInfo){
	if (eventInfo == nullptr)
		return NOTHING_TO_DO;
	return NOTHING_TO_DO;
}

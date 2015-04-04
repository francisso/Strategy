/*
 * AI.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: staslatgttt
 */

#include "AI.h"

AI::AI(int ID,AIMode mode):Player(ID),Mode(mode){
	// TODO Auto-generated constructor stub

}


void AI::OnEvent(EventForPlayer* eventInfo){
	if (eventInfo == nullptr)
		return;
}

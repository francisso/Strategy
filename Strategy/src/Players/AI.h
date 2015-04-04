/*
 * AI.h
 *
 *  Created on: Apr 4, 2015
 *      Author: staslatgttt
 */

#ifndef PLAYERS_AI_H_
#define PLAYERS_AI_H_

#include "Player.h"
#include "../Types.h"

//типы бота
//один @NEUTRAL с @ID=0 будет создан в @Game автоматически
enum AIMode{NEUTRAL,USUAL};

class AI: public Player {
public:
	AI(int ID,AIMode mode);
	virtual ~AI()=default;
	virtual void OnEvent(EventForPlayer* eventInfo);
	const AIMode Mode;
};

#endif /* PLAYERS_AI_H_ */

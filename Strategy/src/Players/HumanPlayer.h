/*
 * HumanPlayer.h
 *
 *  Created on: Apr 4, 2015
 *      Author: staslatgttt
 */

#ifndef PLAYERS_HUMANPLAYER_H_
#define PLAYERS_HUMANPLAYER_H_

#include "Player.h"
#include "../Types.h"

class HumanPlayer: public Player{
public:
	HumanPlayer(int ID);
	virtual ~HumanPlayer()=default;
	void OnEvent(EventForPlayer* eventInfo);
};

#endif /* PLAYERS_HUMANPLAYER_H_ */

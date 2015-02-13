/*
 * Game.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#include "Engine.h"

class Game {
public:
	Game();
	//Game(Engine*);
	virtual ~Game();
	void initializtion();
	void loadResouces();
};

#endif /* GAME_H_ */

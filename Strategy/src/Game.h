/*
 * Game.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#include "Engine.h"

//Основной класс игры
//Организует логику остальных классов
class Game {
public:
	Game(Engine*);
	virtual ~Game();
	void Start();
private:
	//We don't need this constructor
	Game();
	//Constructor initializes all the resources
	void LoadResources();
	//Destructor frees resources
	void FreeResources();
};

#endif /* GAME_H_ */

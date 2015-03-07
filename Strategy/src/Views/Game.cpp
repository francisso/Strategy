/*
 * Game.cpp
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#include "Game.h"
#include "../Constants.h"

Game::Game(Drawable* Background) {
	// TODO Auto-generated constructor stub
	field = new GameField();
	background = Background;
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::Draw(std::function<void (Drawable*)> f) {
	f(background);
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++)
			f(field->grid[i][k].object);
}

void Game::Update(Time t) {
	// TODO implement
}

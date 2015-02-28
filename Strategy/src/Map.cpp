/*
 * Map.cpp
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: anton
 */

#include "Map.h"
#include <cstdlib>
#include <ctime>

Map::Map(std::function<void (Drawable*)> f, SDL_Surface *screen) {
	// Я предпологаю, что textures[6] уже инициализированы
	srand(time (0)); // inisialisetion rand()
	int type = 0;
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int j = 0; j < CELL_Y_NUMBER; j++)
	{
		type = rand() % 6;
		textures[type]->setX(i * CELL_X);
		textures[type]->setY(j * CELL_Y);
		f(textures[type]);
	}

	SDL_SaveBMP(screen, "../res/images/background.bmp");
	background = SDL_LoadBMP("../res/images/background.bmp");
	if (!background)
			throw("Map cannot open background");
}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

void Map::Draw(std::function<void (Drawable*)> f) {
	//TODO implement function
}

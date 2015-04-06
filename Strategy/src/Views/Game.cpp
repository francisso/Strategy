/*
 * Game.cpp
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#include "Game.h"
#include "../Constants.h"
#include <string>
#include <iostream>

Game::Game(Drawable** texture) : Game(texture, new GameField()) {}

Game::Game(Drawable** texture, GameField* field) : field(field), texture(texture) {
	x = 0;
	y = 0;
}

void Game::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const {
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++) {
		texture[field->grid[i][k].textureType]->SetX(static_cast<float>(CELL_X_PIXELS*i));
		texture[field->grid[i][k].textureType]->SetY(static_cast<float>(CELL_Y_PIXELS*k));
		f(texture[field->grid[i][k].textureType], -x, -y);
	}
	f(field->selection, -x, -y);
	this->View::Draw(f);
}

inline int Sign(bool isPositive) {
	return isPositive ? 1 : -1;
}
void Game::MotionMap(Time t)
{
	int X = 0, Y = 0;
	float delta = SpeedMap*t;
	SDL_GetMouseState(&X, &Y);
	// TODO убрать константу 5
	if (X < 5) {
		if (x >= delta)
			x -= delta;
		else x = 0;
	}
	if (Y < 5) {
		if (y >= delta)
			y -= delta;
		else y = 0;
	}
	if (X > X_SIZE_WINDOW - 5) {
		if (x < CELL_X_NUMBER*CELL_X_PIXELS - X_SIZE_WINDOW - delta)
			x += delta;
		else x = CELL_X_NUMBER*CELL_X_PIXELS - X_SIZE_WINDOW;
	}
	if (Y > Y_SIZE_WINDOW - 5) {
		if (y < CELL_Y_NUMBER*CELL_Y_PIXELS - Y_SIZE_WINDOW - delta)
			y += delta;
		else y = CELL_Y_NUMBER*CELL_Y_PIXELS - Y_SIZE_WINDOW;
	}
}
void Game::Update(Time t) {
	MotionMap(t);
}


void Game::OnEvent(SDL_Event* event) {
	switch(event->type)
	{
	case SDL_MOUSEMOTION:
	{
		int X = static_cast<int>(x);
		int Y = static_cast<int>(y);
		int i = (X + event->motion.x) / CELL_X_PIXELS;
		int j = (Y + event->motion.y) / CELL_Y_PIXELS;
		field->selection->SetX(static_cast<float>(i*CELL_X_PIXELS));
		field->selection->SetY(static_cast<float>(j*CELL_Y_PIXELS));
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		auto X = static_cast<int>(x);
		auto Y = static_cast<int>(y);
		auto i = (X + event->button.x) / CELL_X_PIXELS;
		auto j = (Y + event->button.y) / CELL_Y_PIXELS;
		field->grid[i][j].textureType +=1;
		field->grid[i][j].textureType %=TEXTURE_COUNT;
		break;
	}
	case SDL_QUIT: {
		SaveMap(DefaultMapPath); break;
	}
	}
}


void Game::SaveMap (const char* path) {
	std::cout << "Saving map to " << path << std::endl;
	std::ofstream file;
	file.open(path);
	std::string line;
	while (Getline(&line, field))
		file << line << std::endl;
	file.close();
}

int Game::Getline(std::string* line, GameField* field) {
	static int lineNumber = 0;
	line->clear();
	for (int i =0; i < CELL_X_NUMBER; i++)
		line->append(std::to_string(field->grid[lineNumber][i].textureType));
	std::cout << *line << std::endl;
	return (++lineNumber > CELL_Y_NUMBER) ? 0 : 1;
}

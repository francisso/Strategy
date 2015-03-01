/*
 * Engine.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "Engine.h"
#include "../Constants.h"

Engine::Engine() {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	        printf( "Unable to init SDL: %s", SDL_GetError());
	        return;
	}
	screen = SDL_SetVideoMode(CELL_X_NUMBER*CELL_X, CELL_Y_NUMBER*CELL_Y, 16,
								SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (!screen)
	{
	    printf("Can't set videomode: %s", SDL_GetError());
	    return;
	}
	view = nullptr;
}

Engine::~Engine() {
	// TODO Auto-generated destructor stub
}

void Engine::LoadResources(){
	SDL_Rect src = {0, 0, CELL_X, CELL_Y};
	texture[GROUND] = new GameObject(src, "res/images/ground.bmp");
	texture[WATER]  = new GameObject(src, "res/images/water.bmp");
	texture[SAND]   = new GameObject(src, "res/images/sand.bmp");
	texture[FOREST] = new GameObject(src, "res/images/forest.bmp");
	texture[MOUNTIAN] = new GameObject(src, "res/images/mountian.bmp");
	texture[SWAMP]  = new GameObject(src, "res/images/swamp.bmp");
}

void Engine::FreeResources(){
	// TODO implement function
}

void Engine::Run(){
	// TODO implement function
	DrawView(view);
}

//
void Engine::Draw(Drawable* drawable)
{
	if (drawable == nullptr)
		return;
	SDL_BlitSurface(drawable->GetImage(),
			drawable->GetDestRect(),
			screen,
			drawable->GetSrcRect());
}
void Engine::DrawView(View* view) {
	if (view == nullptr)
		throw("Engine view is null");

	//Передаем view функцию, при помощи которой можно
	// рисовать SDL_Surface
	auto f = [this] (Drawable* drawable) {
		this->Draw(drawable);
	};
	view->Draw(f);
	SDL_Flip(screen);
}

Drawable* Engine::CreateBackgroung(GameField* field)
{
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int j = 0; j < CELL_Y_NUMBER; j++)
	{
		texture[field->field[i][j].type.texstura]->setX(i * CELL_X);
		texture[field->field[i][j].type.texstura]->setY(j * CELL_Y);
		Draw(texture[field->field[i][j].type.texstura]);
	}

	SDL_SaveBMP(screen, "res/images/background.bmp");
	SDL_Rect src = {0, 0, CELL_X_NUMBER*CELL_X, CELL_Y_NUMBER*CELL_Y};
	GameObject* background = new GameObject(src, "res/images/background.bmp");
	if (!background->GetImage())
		throw("Engine cannot open background");
	return background;
}

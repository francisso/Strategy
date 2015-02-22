/*
 * Engine.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "Engine.h"

Engine::Engine() {
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	        printf( "Unable to init SDL: %s", SDL_GetError());
	        return;
	}
	screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
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
	// TODO implement function
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
	SDL_BlitSurface(drawable->GetImage(),
			drawable->GetSrcRect(),
			screen,
			drawable->GetDestRect());
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

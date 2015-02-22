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
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
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
	//DrawView(view);
	SDL_Surface* im = SDL_LoadBMP("test.bmp");
	SDL_Rect src, desc;
	src.x = 0;
	src.y = 0;
	src.w = 100;
	src.h = 100;
	desc.x = 0;
	desc.y = 0;
	desc.w = 100;
	desc.h = 100;
	SDL_BlitSurface(im, &src, screen, &desc);
	SDL_Flip(screen);
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
	//Передаем view функцию, при помощи которой можно
	// рисовать SDL_Surface
	auto f = [this] (Drawable* drawable) {
		this->Draw(drawable);
	};
	view->Draw(f);
}

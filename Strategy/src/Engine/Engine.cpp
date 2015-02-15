/*
 * Engine.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "Engine.h"

Engine::Engine() {
	// TODO Auto-generated constructor stub
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
}

//
void Engine::DrawView(View view) {
	//Передаем view функцию, при помощи которой можно
	// рисовать SDL_Surface
	view.Draw([this] (Drawable* drawable) {
			this->graphics->Draw(drawable);
			});
}

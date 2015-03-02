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

void nothin() {
	return;
}


void Engine::Run(){
	std::thread threadDraw(ThreadDraw, std::ref(view), std::ref(screen));
	//необходимо отсоединять потоки, чтобы не было проблем по выходу за область видимости
	threadDraw.detach();
	std::thread threadUpdate(ThreadUpdate, std::ref(view));
	threadUpdate.detach();
}

void Engine::ThreadDraw(View* view, SDL_Surface* screen) {
	while(1)
		DrawView(view, screen);
}

void Engine::ThreadUpdate(View* view) {
	auto lastCalled = clock();
	clock_t currentTime;
	while (1) {
		currentTime = clock();
		Time delta = (currentTime-lastCalled)*1.0/CLOCKS_PER_SEC;
		lastCalled=currentTime;
		view->Update(delta);
	}
}

void Engine::Draw(Drawable* drawable, SDL_Surface* screen)
{
	if (drawable == nullptr)
		return;
	SDL_BlitSurface(drawable->GetImage(),
			drawable->GetDestRect(),
			screen,
			drawable->GetSrcRect());
}

void Engine::DrawView(View* view, SDL_Surface* screen) {
	if (view == nullptr)
		throw("Engine view is null");

	//Передаем view функцию, при помощи которой можно
	// рисовать SDL_Surface
	auto f = [&screen] (Drawable* drawable) {
		Draw(drawable, screen);
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
		Draw(texture[field->field[i][j].type.texstura], screen);
	}

	SDL_SaveBMP(screen, "res/images/background.bmp");
	SDL_Rect src = {0, 0, CELL_X_NUMBER*CELL_X, CELL_Y_NUMBER*CELL_Y};
	GameObject* background = new GameObject(src, "res/images/background.bmp");
	if (!background->GetImage())
		throw("Engine cannot open background");
	return background;
}

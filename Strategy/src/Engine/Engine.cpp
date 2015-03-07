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
	screen = SDL_SetVideoMode(CELL_X_NUMBER*CELL_X_PIXELS, CELL_Y_NUMBER*CELL_Y_PIXELS, 16,
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
	SDL_Rect src = {0, 0, CELL_X_PIXELS, CELL_Y_PIXELS};
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
	if (MULTUTHREADING) {
		std::thread threadDraw(ThreadDraw, std::ref(view), std::ref(screen));
		//необходимо отсоединять потоки, чтобы не было проблем по выходу за область видимости
		threadDraw.detach();
		std::thread threadUpdate(ThreadUpdate, std::ref(view));
		threadUpdate.detach();
	}
	else {
		GameCycle();
	}
}

void Engine::ThreadDraw(View* view, SDL_Surface* screen) {
	clock_t lastCalled = clock();
	clock_t currentTime;
	const clock_t min_delta = CLOCKS_PER_SEC/DRAW_FPS;
	while(1) {
		currentTime = clock();
		if (currentTime-lastCalled < min_delta)
			continue;
		DrawView(view, screen);
		lastCalled = currentTime;
	}

}

void Engine::ThreadUpdate(View* view) {
	auto lastCalled = clock();
	clock_t currentTime;
	const clock_t min_delta = CLOCKS_PER_SEC/UPDATE_FPS;
	while (1) {
		currentTime = clock();
		clock_t delta = (currentTime-lastCalled);
		if (delta < min_delta)
			continue;
		lastCalled=currentTime;
		view->Update(delta*1.0/CLOCKS_PER_SEC);
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
	for (int j = 0; j < CELL_Y_NUMBER; j++) {
		texture[field->grid[i][j].type.textureType]->setX(i * CELL_X_PIXELS);
		texture[field->grid[i][j].type.textureType]->setY(j * CELL_Y_PIXELS);
		Draw(texture[field->grid[i][j].type.textureType], screen);
	}

	SDL_SaveBMP(screen, "res/images/background.bmp");
	SDL_Rect src = {0, 0, CELL_X_NUMBER*CELL_X_PIXELS, CELL_Y_NUMBER*CELL_Y_PIXELS};
	GameObject* background = new GameObject(src, "res/images/background.bmp");
	if (!background->GetImage())
		throw("Engine cannot open background");
	return background;
}


void Engine::GameCycle() {
	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = CLOCKS_PER_SEC / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;
	clock_t next_game_tick = clock();
	int loops;
	float interpolation;
	bool game_is_running = true;
	while( game_is_running ) {
        loops = 0;
        while( clock() > next_game_tick && loops < MAX_FRAMESKIP) {
        	interpolation = float( clock() + SKIP_TICKS - next_game_tick )
	    		                        / float( SKIP_TICKS );
	    	view->Update(interpolation);
	    	next_game_tick += SKIP_TICKS;
	    	loops++;
	    }
	    DrawView(view, screen);
	}
}

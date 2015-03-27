/*
 * Engine.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "Engine.h"


Engine::Engine() : view(nullptr) {
	if ( SDL_Init( SDL_INIT_VIDEO) < 0 )
	{
	        printf( "Unable to init SDL: %s", SDL_GetError());
	        return;
	}
	//Создаем окно
	Uint32 flags =  SDL_HWSURFACE | SDL_DOUBLEBUF;
	if (FULLSCREEN)
		flags |= SDL_FULLSCREEN;
	screen = SDL_SetVideoMode(0, 0, 32, flags);
	if (!screen) {
	    printf("Can't set videomode: %s", SDL_GetError());
	    return;
	}
	X_SIZE_WINDOW = static_cast<CoordinateType>(screen->w);
	Y_SIZE_WINDOW = static_cast<CoordinateType>(screen->h);
	printf("screen size: %d x %d\n", screen->w, screen->h);
}

Engine::~Engine() {
	SDL_Quit();
}

Drawable** Engine::LoadResources(){
	SDL_Rect src = {0, 0, CELL_X_PIXELS, CELL_Y_PIXELS};
	texture[GROUND] = new GameObject(src, "res/images/ground.bmp");
	texture[WATER]  = new GameObject(src, "res/images/water.bmp");
	texture[SAND]   = new GameObject(src, "res/images/sand.bmp");
	texture[FOREST] = new GameObject(src, "res/images/forest.bmp");
	texture[MOUNTIAN] = new GameObject(src, "res/images/mountian.bmp");
	texture[SWAMP]  = new GameObject(src, "res/images/swamp.bmp");
	//auto x = new GameObject(src, "res/images/selection.bmp");
	return texture;
}

void Engine::FreeResources(){
	// TODO implement function
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
		view->Update(static_cast<float>(delta)/CLOCKS_PER_SEC);
	}
}

void Engine::Draw(Drawable* drawable, SDL_Surface* screen, CoordinateType X0, CoordinateType Y0) {
	if (drawable == nullptr)
		return;
	SDL_Rect src(*drawable->GetSrcRect());
	X0 += src.x;
	Y0 += src.y;
	src.x = static_cast<short int>(X0);
	src.y = static_cast<short int>(Y0);
	if (src.x + src.w < 0 || src.y + src.h < 0 ||
				src.x > X_SIZE_WINDOW || src.y > Y_SIZE_WINDOW)
			return;
	SDL_BlitSurface(drawable->GetImage(),
			drawable->GetDestRect(),
			screen,
			&src);
}

void Engine::DrawView(View* view, SDL_Surface* screen) {
	if (view == nullptr)
		throw("Engine view is null");

	//Передаем view функцию, при помощи которой можно
	// рисовать SDL_Surface
	auto f = [&screen] (Drawable* drawable, CoordinateType X0, CoordinateType Y0) {
		Draw(drawable, screen, X0, Y0);
	};
	view->Draw(f);
	SDL_Flip(screen);
}

Drawable* Engine::CreateBackgroung(GameField* field) const
{
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int j = 0; j < CELL_Y_NUMBER; j++) {
		texture[field->grid[i][j].textureType]->SetX(static_cast<float>(i * CELL_X_PIXELS));
		texture[field->grid[i][j].textureType]->SetY(static_cast<float>(j * CELL_Y_PIXELS));
		Draw(texture[field->grid[i][j].textureType], screen);
	}

	SDL_SaveBMP(screen, "res/images/background.bmp");
	SDL_Rect src = {0, 0, CELL_X_NUMBER*CELL_X_PIXELS, CELL_Y_NUMBER*CELL_Y_PIXELS};
	GameObject* background = new GameObject(src, "res/images/background.bmp");
	if (!background->GetImage())
		throw("Engine cannot open background");
	return background;
}

void Engine::ProcessInput(View* view)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) // Пока есть хоть одно необработанное событие
	{
		view->OnEvent(&event);
		switch(event.type)
		{
		case SDL_QUIT:
		{
	        game_is_running = false;
	       	break;
		}
	    case SDL_KEYDOWN:
        {
        	switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            {
            	game_is_running = false;
            	break;
            }
            default:
            	break;
            }
        }
		}
	}
}

void Engine::GameCycle() {
	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = CLOCKS_PER_SEC / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;
	clock_t next_game_tick = clock();
	int loops;
	float interpolation;
	while( game_is_running ) {
        loops = 0;
        ProcessInput(view);
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

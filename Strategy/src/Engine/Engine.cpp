/*
 * Engine.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "Engine.h"


Engine::Engine() : view(nullptr) {
	frame = nullptr;
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
	X_SIZE_WINDOW = static_cast<float>(screen->w);
	Y_SIZE_WINDOW = static_cast<float>(screen->h);
	printf("screen size: %d x %d\n", screen->w, screen->h);
}

Engine::~Engine() {
	SDL_Quit();
}

Drawable** Engine::LoadResources(){
	SDL_Rect src = {0, 0, CELL_X_PIXELS, CELL_Y_PIXELS};
	texture[GROUND] = new PlayingObject(src, "res/images/ground.bmp");
	texture[WATER]  = new PlayingObject(src, "res/images/water.bmp");
	texture[SAND]   = new PlayingObject(src, "res/images/sand.bmp");
	texture[FOREST] = new PlayingObject(src, "res/images/forest.bmp");
	texture[MOUNTIAN] = new PlayingObject(src, "res/images/mountian.bmp");
	texture[SWAMP]  = new PlayingObject(src, "res/images/swamp.bmp");
	SDL_Rect src_frame = {0, 0, 120, 80};
	frame = new PlayingObject(src_frame, "res/images/frame.bmp");
	//auto x = new GameObject(src, "res/images/selection.bmp");
	return texture;
}

void Engine::FreeResources(){
	// TODO implement function
}

Drawable* Engine::CreateBackgroungStatusBar() const{
	SDL_Rect left_frame = {0, 0, 20, 80};
	SDL_Rect right_frame = {20, 0, 20, 80};
	SDL_Rect high_frame = {40, 0, 80, 20};
	SDL_Rect low_frame = {40, 20, 80, 20};
	SDL_Rect corner_frame = {40, 40, 20, 20};
//	SDL_Rect violet_frame = {40, 60, 20, 20};
//b	SDL_Rect back_frame = {60, 40, 10, 10};

	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 0, 255));
/*
	// фон строки состояния
	frame->SetSrcRect(&back_frame);
	for (int k = 0; k <= X_SIZE_WINDOW/10; k++)
	for (int i = 0; i <= HIGH_STATUS_BAR/10; i++){
		frame->SetX(static_cast<float>(k*10));
		frame->SetY(X_SIZE_WINDOW + static_cast<float>(-HIGH_STATUS_BAR + i*10));
		Draw(frame, screen);
	}
*/
	SDL_Rect s_bar_rect = {20,
			static_cast<Sint16>(Y_SIZE_WINDOW - HIGH_STATUS_BAR - 20),
			static_cast<Uint16>(X_SIZE_WINDOW - 40),
			HIGH_STATUS_BAR
	};
	SDL_FillRect(screen, &s_bar_rect, SDL_MapRGB(screen->format, 196, 142, 24));
	s_bar_rect.h = 20;
	SDL_FillRect(screen, &s_bar_rect, SDL_MapRGB(screen->format, 146, 82, 84));
	// левая линия
	frame->SetSrcRect(&left_frame);
	frame->SetX(0);
	for (int i = 0; i <= X_SIZE_WINDOW/80; i++){
		frame->SetY(static_cast<float>(i*80));
		Draw(frame, screen);
	}
	// правая линия
	frame->SetSrcRect(&right_frame);
	frame->SetX(X_SIZE_WINDOW - 20);
	for (int i = 0; i <= X_SIZE_WINDOW/80; i++) {
		frame->SetY(static_cast<float>(i*80));
		Draw(frame, screen);
	}
	// верхняя линия
	frame->SetSrcRect(&high_frame);
	frame->SetY(0);
	for (int i = 0; i <= X_SIZE_WINDOW/80; i++) {
		frame->SetX(static_cast<float>(i*80));
		Draw(frame, screen);
	}
	// нижняя линия
	frame->SetSrcRect(&low_frame);
	frame->SetY(Y_SIZE_WINDOW - 20);
	for (int i = 0; i <= X_SIZE_WINDOW/80; i++) {
		frame->SetX(static_cast<float>(i*80));
		Draw(frame, screen);
	}
	// углы
	frame->SetSrcRect(&corner_frame);
	frame->SetX(0);
	frame->SetY(0);
	Draw(frame, screen);
	frame->SetX(X_SIZE_WINDOW - 20);
	frame->SetY(0);
	Draw(frame, screen);
	frame->SetX(0);
	frame->SetY(Y_SIZE_WINDOW - 20);
	Draw(frame, screen);
	frame->SetX(X_SIZE_WINDOW - 20);
	frame->SetY(Y_SIZE_WINDOW - 20);
	Draw(frame, screen);

	// сохранение фона
	SDL_SaveBMP(screen, "res/images/background_status_bar.bmp");
	SDL_Rect src = {0, 0, static_cast<Uint16>(X_SIZE_WINDOW), static_cast<Uint16>(Y_SIZE_WINDOW)};
	PlayingObject* background = new PlayingObject(src, "res/images/background_status_bar.bmp");
	if (!background->GetImage())
		throw("Engine cannot open background");
	return background;
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

void Engine::Draw(Drawable* drawable, SDL_Surface* screen, float X0, float Y0) {
	if (drawable == nullptr)
		return;
	SDL_Rect dest(*drawable->GetDestRect());
	X0 += dest.x;
	Y0 += dest.y;
	dest.x = static_cast<short int>(X0);
	dest.y = static_cast<short int>(Y0);
	if (dest.x + dest.w < 0 || dest.y + dest.h < 0 ||
				dest.x > X_SIZE_WINDOW || dest.y > Y_SIZE_WINDOW)
			return;
	SDL_BlitSurface(drawable->GetImage(),
			drawable->GetSrcRect(),
			screen,
			&dest);
}

void Engine::DrawView(View* view, SDL_Surface* screen) {
	if (view == nullptr)
		throw("Engine view is null");

	//Передаем view функцию, при помощи которой можно
	// рисовать SDL_Surface
	auto f = [&screen] (Drawable* drawable, float X0, float Y0) {
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
	PlayingObject* background = new PlayingObject(src, "res/images/background.bmp");
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

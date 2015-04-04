//============================================================================
// Name        : Strategy.cpp
// Author      : Author
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <iostream>

#include "Engine/Engine.h"
#include "Views/View.h"
#include "Views/ViewCreator.h"
#include "Views/Game.h"
#include "Views/GameField.h"
#include "Views/StatusBar.h"
#include "FieldBuilder.h"
#include "Units/Archer.h"
#include "Units/Action.h"
#include "Constants.h"

// Размеры окна
CoordinateType X_SIZE_WINDOW;
CoordinateType Y_SIZE_WINDOW;

int main() {
	std::cout << "I'm working" << std::endl;
	try
	{
		Engine* engine = new Engine();
		Drawable** texture = engine->LoadResources();
		GameField* field = FieldBuilder::CreateField();
		// создание game
		Uint16 w_game_window = static_cast<Uint16>(X_SIZE_WINDOW - 2*FRAME);
		Uint16 h_game_window = static_cast<Uint16>(Y_SIZE_WINDOW - HIGH_STATUS_BAR - 2*FRAME);
		SDL_Rect gameRect { FRAME, FRAME, w_game_window, h_game_window};
		auto game = new Game(texture, field, gameRect);
		// создание status bar
		Drawable* back_status_bar = engine->CreateBackgroungStatusBar();
		StatusBar* status_bar = new StatusBar();
		status_bar->SetBackground(back_status_bar);
		View* main_view = new View();
		main_view->AddView(status_bar);
		main_view->AddView(game);
		//Здесь это времеено, создание лучника.
		SDL_Rect src = {100,100,80,80};
		/*int cell_x = 2;
		int cell_y = 2;*/
		auto archer = new Archer(src, "res/images/test.bmp");
		archer->SetX(200.0);
		archer->SetY(200.0);
		archer->DirectMoveToCell(5,4);
		archer->DirectMoveToCell(2,2,false);
		game->AddUnit(archer);
		engine->SetView(main_view);
		engine->Run();
	}
	catch (std::exception* e)
	{
		std::cout << e->what() <<std::endl;
	}
	catch (const char* e)
	{
		std::cout << "An error has occurred" <<std::endl;
		std::cout << e <<std::endl;
	}
	return 0;
}

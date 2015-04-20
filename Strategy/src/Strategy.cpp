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
#include "Constants.h"
#include "Drawable/GameObjects/Action.h"
#include "Drawable/GameObjects/Units/Archer.h"
#include "Players/HumanPlayer.h"

// Размеры окна
float X_SIZE_WINDOW;
float Y_SIZE_WINDOW;

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
		main_view->AddView(game);
		main_view->AddView(status_bar);

		//создание игрока-человека
		HumanPlayer* Player_1=new HumanPlayer(1,RED,"Player 1");
		game->AddPlayer(Player_1);
		game->SwitchPlayer(1);

		//Здесь это времеено, создание лучника.
		SDL_Rect src1 = {0,0,80,80};
		SDL_Rect src2 = {100,100,80,80};
		/*int cell_x = 2;
		int cell_y = 2;*/
		auto archer1 = new Archer(src1, "res/images/unit.bmp",1);
		archer1->SetX(200.0);
		archer1->SetY(200.0);
		auto archer2 = new Archer(src2, "res/images/test.bmp",1);
		archer1->SetX(160.0);
		archer1->SetY(400.0);
		//archer->DirectMoveToCell(5,4);
		//archer->DirectMoveToCell(2,2,false);
		game->AddUnit(archer1);
		game->AddUnit(archer2);
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
	catch (std::string e)
		{
			std::cout << "An error has occurred" <<std::endl;
			std::cout << e <<std::endl;
		}
	return 0;
}

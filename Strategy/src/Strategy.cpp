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
#include "FieldBuilder.h"
#include "Units/Archer.h"
#include "Constants.h"



int main() {
	std::cout << "I'm working" << std::endl;
	try
	{
		Engine* engine = new Engine();
		engine->LoadResources();
		GameField* field = FieldBuilder::CreateField();
		Drawable* back = engine->CreateBackgroung(field);
		auto game = new Game(back, field);
		//Здесь это времеено, создание лучника.
		SDL_Rect src = {100,100,160,160};
		int cell_x = 5;
		int cell_y = 3;
		auto archer = new Archer(src, "res/images/test.bmp");
		archer->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
		archer->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
		game->AddUnitAtCell(archer,cell_x, cell_y);
		cell_x = 7;
		cell_y = 3;
		auto archer1 = new Archer(src, "res/images/test.bmp");
		archer1->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
		archer1->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
		game->AddUnitAtCell(archer1,cell_x, cell_y);

		engine->SetView(game);
		engine->Run();
		//зацикливаемся, чтобы не закрылось открывшеяся окно
		while(1);
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

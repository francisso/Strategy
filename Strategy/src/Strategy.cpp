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
#include "Units/Action.h"
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
		SDL_Rect src = {100,100,80,80};
		int cell_x = 2;
		int cell_y = 2;
		auto archer = new Archer(src, "res/images/test.bmp");
		archer->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
		archer->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
		archer->DirectMoveToCell(5,4);
		archer->DirectMoveToCell(2,2,false);
		game->AddUnitAtCell(archer,cell_x, cell_y);
		engine->SetView(game);
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

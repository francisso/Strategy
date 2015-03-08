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



int main() {
	std::cout << "I'm working" << std::endl;
	try
	{
		Engine* engine = new Engine();
		engine->LoadResources();
		GameField* field = FieldBuilder::CreateField();
		Drawable* back = engine->CreateBackgroung(field);
		back = nullptr;
		auto game = new Game(back, field);
		SDL_Rect src = {0,0,360,360};
		auto archer = new Archer(src, "res/images/test.bmp");
		game->AddDrawable(archer);
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

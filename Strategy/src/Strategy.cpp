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
		auto bar = ViewCreator::CreateStatusBar("Views/MainView.xml");
		if (bar == nullptr)
			std::cout<< "bar error" << std::endl;
		auto game = new Game(texture, field);
		game->AddView(bar);
		game->SetBar(bar);
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

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


int main() {
	std::cout << "I'm working fine";
	try
	{
		//Game* game = new Game();
		//game->Start();
		View* view = new View();
		// TODO load view from file
		// Загружаем из файла интерфейс

		Engine* engine = new Engine();
		engine->SetView(view);
		engine->Run();

	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
	return 0;
}

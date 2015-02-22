//============================================================================
// Name        : Strategy.cpp
// Author      : Author
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <iostream>
#include <string>

#include "Engine/Engine.h"
#include "Views/View.h"


int main() {
	std::cout << "I'm working fine";
	try
	{
		View* view = new View();
		SDL_Rect rect ;
		rect.x = 0;
		rect.y = 0;
		rect.w = 100;
		rect.h = 100;
		//в этой строчке происходит ошибка
		//путь у меня абсолютный, на всякий случай
		//auto d = new GameObject(&rect, "/home/anton/git/Coursework/Strategy/res/images/test.bmp");
		//в общем, путь должен быть каким-то таким
		auto d = new GameObject(&rect, "test.bmp");
		view->AddDrawable(d);

		// TODO load view from file
		// Загружаем из файла интерфейс


		Engine* engine = new Engine();
		engine->SetView(view);
		engine->Run();
		//зацикливаемся, чтобы не закрылось открывшеяся окно
		while(1);

	}
	catch (std::exception* e)
	{
		std::cout << e->what();
	}
	return 0;
}

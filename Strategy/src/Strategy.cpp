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
#include <random>


#include "Constants.h"
#include "Engine/Engine.h"
#include "Views/View.h"
#include "Views/ViewCreator.h"
#include "Views/GameField.h"
#include "FieldBuilder.h"

int main() {
	std::cout << "I'm working" << std::endl;
	try
	{
		View* view = ViewCreator::CreateView("Views/MainView.xml");
		Engine* engine = new Engine();
		engine->LoadResources();
		engine->SetView(view);
		GameField* field = FieldBuilder::CreateField();
		Drawable* back = engine->CreateBackgroung(field);
		view->AddDrawable(back);
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

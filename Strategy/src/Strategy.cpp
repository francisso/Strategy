//============================================================================
// Name        : Strategy.cpp
// Author      : Author
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <iostream>
#include <list>

#include "Engine/Engine.h"
#include "Views/ViewCreator.h"
#include "Views/Order.h"
#include "Drawable/GameObjects/ObjectFactory.h"

// Размеры окна
float X_SIZE_WINDOW;
float Y_SIZE_WINDOW;
std::list<Order> list_of_orders;

const char* ObjectFactory::unitConfigs="res/object_configs/Units.xml";
const char* ObjectFactory::buildingConfigs="res/object_configs/Buildings.xml";
const char* ObjectFactory::lootConfigs="res/object_configs/Loot.xml";
const char* ObjectFactory::environmentConfigs="res/object_configs/Environment.xml";

int main() {
	std::cout << "I'm working" << std::endl;
	try
	{
		Engine* engine = new Engine();
		View* main_view = ViewCreator::CreateMainView(engine);
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
	catch (std::string& e)
		{
			std::cout << "An error has occurred" <<std::endl;
			std::cout << e <<std::endl;
		}
	return 0;
}

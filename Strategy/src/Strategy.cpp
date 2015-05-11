//============================================================================
// Name        : Strategy.cpp
// Author      : Author
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <iostream>
#include <vector>

#include "Engine/Engine.h"
#include "Views/View.h"
#include "Views/ViewCreator.h"
#include "Views/Game/Game.h"
#include "Views/Game/GameField.h"
#include "Views/StatusBar/StatusBar.h"
#include "Views/Game/FieldBuilder.h"
#include "Constants.h"
#include "Drawable/GameObjects/Action.h"
#include "Drawable/GameObjects/Units/Archer.h"
#include "Drawable/GameObjects/Buildings/Tower.h"
#include "Players/HumanPlayer.h"
#include "Views/StatusBar/StatusObject.h"
#include "Views/Order.h"
#include "Drawable/GameObjects/ObjectFactory.h"

// Размеры окна
float X_SIZE_WINDOW;
float Y_SIZE_WINDOW;
std::vector<Order> vector_of_orders;

const char* ObjectFactory::unitConfigs="ObjectConfigs/Units.xml";
const char* ObjectFactory::buildingConfigs="ObjectConfigs/Buildings.xml";
const char* ObjectFactory::lootConfigs="ObjectConfigs/Loot.xml";
const char* ObjectFactory::environmentConfigs="ObjectConfigs/Environment.xml";


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
		// создание amount_object
		StatusBar* amount_object = new StatusBar();
		amount_object->SetBackground(engine->CreateBackgroungStatusBar_Amount());
		// создание StatusObject
		SDL_Rect src_text = {30, 120, 80, 80};
		SDL_Rect src = {0, 0, 80, 80};
		auto unit_status_draw = new Draw(src, "res/images/unit_for_status_bar.bmp");
		unit_status_draw->SetX(20);
		unit_status_draw->SetY(20);
		StatusObject* unit_status = new StatusObject(unit_status_draw, src_text);
		unit_status->SetText("3000");
		amount_object->AddStatusObject(unit_status);
		// создание amount_object
		StatusBar* action_panel = new StatusBar();
		action_panel->SetBackground(engine->CreateBackgroungStatusBar_Action());
		status_bar->AddView(amount_object);
		status_bar->AddView(action_panel);
		View* main_view = new View();
		main_view->AddView(game);
		main_view->AddView(status_bar);

		//создание игрока-человека
		HumanPlayer* Player_1=new HumanPlayer(1,RED,"Player 1");
		game->AddPlayer(Player_1);
		game->SwitchPlayer(1);

		//Здесь это времеено, создание лучника.
		//SDL_Rect src1 = {0,0,40,40};
		//auto archer1 = new Archer(src1, "res/images/unit.bmp",1);
		auto archer1 = ObjectFactory::CreateUnit(UnitType::ARCHER,1,0,0);
		game->AddUnitAtCell(archer1,2,2);

		SDL_Rect src2 = {0,0,40,40};
		auto archer2 = new Archer(src2, "res/images/unit.bmp",1);
		archer2->SetX(400.0);
		archer2->SetY(240.0);
		game->AddUnit(archer2);

		SDL_Rect src3 = {0,0,40,40};
		auto archer3 = new Archer(src3, "res/images/unit.bmp",1);
		archer3->SetX(240.0);
		archer3->SetY(160.0);
		game->AddUnit(archer3);

		SDL_Rect src4 = {0,0,40,40};
		auto archer4 = new Archer(src4, "res/images/unit.bmp",1);
		archer4->SetX(320.0);
		archer4->SetY(160.0);
		game->AddUnit(archer4);

		SDL_Rect src5 = {0,0,80,80};
		auto tower1  = new Tower(src5, "res/images/test.bmp",1);
		game->AddBuildingAtCell(tower1,8,8);

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

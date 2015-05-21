/*
 * ViewCreator.cpp
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#include "ViewCreator.h"


View* ViewCreator::CreateMainView(Engine* engine)
{
	View* main_view = new View();
	View* status_bar = CreateStatusBar(engine);
	View* game = CreateGame(engine);
	main_view->AddView(game);
	main_view->AddView(status_bar);
	return main_view;
}

View* ViewCreator::CreateGame(Engine* engine){
	Drawable** texture = engine->LoadResources();
	GameField* field = FieldBuilder::CreateField();

	// создание game
	Uint16 w_game_window = static_cast<Uint16>(X_SIZE_WINDOW - 2*FRAME);
	Uint16 h_game_window = static_cast<Uint16>(Y_SIZE_WINDOW - HIGH_STATUS_BAR - 2*FRAME);
	SDL_Rect gameRect { FRAME, FRAME, w_game_window, h_game_window};
	auto game = new Game(texture, field, gameRect);

	//создание игрока-человека
	HumanPlayer* Player_1=new HumanPlayer(1,RED,"Player 1");
	game->AddPlayer(Player_1);
	game->SwitchPlayer(1);

	//Здесь это времеено, создание лучника.
	/*
	SDL_Rect src1 = {0,0,40,40};
	auto archer1 = new Archer(src1, "res/images/archer.bmp",1);
	game->AddUnitAtCell(archer1,2,2);

	SDL_Rect src2 = {0,0,40,40};
	auto archer2 = new Archer(src2, "res/images/archer.bmp",1);
	archer2->SetX(400.0);
	archer2->SetY(240.0);
	game->AddUnit(archer2);

	SDL_Rect src3 = {0,0,40,40};
	auto archer3 = new Archer(src3, "res/images/archer.bmp",1);
	archer3->SetX(240.0);
	archer3->SetY(160.0);
	game->AddUnit(archer3);

	SDL_Rect src4 = {0,0,40,40};
	auto archer4 = new Archer(src4, "res/images/archer.bmp",1);
	archer4->SetX(320.0);
	archer4->SetY(160.0);
	game->AddUnit(archer4);

	SDL_Rect src5 = {0,0,80,80};
	auto tower1  = new Tower(src5, "res/images/test.bmp",1);
	game->AddBuildingAtCell(tower1,8,8);*/

	game->AddUnitAtCell(ObjectFactory::CreateUnit(ARCHER,1),2,2);
	game->AddUnitAtCell(ObjectFactory::CreateUnit(ARCHER,1),2,3);
	//game->AddUnitAtCell(ObjectFactory::CreateUnit(ARCHER,1),3,2);
	//game->AddUnitAtCell(ObjectFactory::CreateUnit(ARCHER,1),3,3);
	game->AddBuildingAtCell(ObjectFactory::CreateBuilding(FORT,1), 5,5);

	return game;
}
StatusBar* ViewCreator::CreateStatusBar_Amount(Engine* engine){
	// создание amount_object
	auto make_amount_orders = [](StatusBar* status_bar){
		std::list<Order>::iterator next_ord;
		std::list<Order>::iterator ord = list_of_orders.begin();
		bool flag = true;
		while ( ord != list_of_orders.end()) {
			next_ord = ++ord;
			ord--;
			if (ord->receiver == STATUS_BAR_AMOUNT){
				if (ord->order == SELECTED){
					if (flag)
						status_bar->ClearStatusObjects();
					std::vector<AmountOfUnit> counters = ord->counters;

					if (counters.size() > 0 && counters[0].object_type == BUILDING && flag){
						SDL_Rect src = {0, 0, 160, 160};
						SDL_Rect src_text = {200, 95, 280, 80};
						auto buiding_status_draw = new Draw(src, "res/images/test.bmp");
						buiding_status_draw->SetX(20);
						buiding_status_draw->SetY(20);
						StatusObject* building_status = new StatusObject(buiding_status_draw, src_text);
						building_status->SetText("Castle");
						building_status->SetColorText(255, 255, 55);
						building_status->SetSizeText(30);
						status_bar->AddStatusObject(building_status);
					} else
					for (unsigned int i = 0; i < counters.size() && flag; i++){
						SDL_Rect src = {0, 0, 80, 80};
						SDL_Rect src_text = {static_cast<Sint16>(30 + 100*i), 120, 80, 80};
						auto unit_status_draw = new Draw(src, "res/images/unit_for_status_bar.bmp");
						unit_status_draw->SetX(static_cast<float>(20 + 100*i));
						unit_status_draw->SetY(20);
						StatusObject* unit_status = new StatusObject(unit_status_draw, src_text);
						char text[80];
						sprintf(text, "%d", counters[i].amount);
						unit_status->SetText(text);
						status_bar->AddStatusObject(unit_status);
					}

					flag = false;
					list_of_orders.erase(ord);
				}
			}
			ord = next_ord;
		}
	};
	StatusBar* amount_object = new StatusBar(make_amount_orders);
	amount_object->SetBackground(engine->CreateBackgroungStatusBar_Amount());
	return amount_object;
}
StatusBar* ViewCreator::CreateStatusBar_Action(Engine* engine){
	// создание action_panel
	auto make_action_orders = [](StatusBar* status_bar){
		std::list<Order>::iterator next_ord;
		std::list<Order>::iterator ord = list_of_orders.begin();
		bool flag = true;
		while ( ord != list_of_orders.end()) {
			next_ord = ++ord;
			ord--;
			if (ord->receiver == STATUS_BAR_ACTION){
				if (ord->order == SELECTED){
					if (flag)
						status_bar->ClearStatusObjects();
					std::vector<AmountOfUnit> counters = ord->counters;
					if (counters.size() > 0 && counters[0].object_type == BUILDING && flag){
						SDL_Rect src = {0, 0, 160, 70};
						SDL_Rect text_src = {35, 45, 140, 30};
						auto button_status_draw = new Draw(src, "res/images/button.bmp");
						button_status_draw->SetX(20);
						button_status_draw->SetY(20);
						StatusObject* button_status = new StatusObject(button_status_draw, text_src);
						button_status->SetText("Create unit");
						status_bar->AddStatusObject(button_status);
					}
					flag = false;
					list_of_orders.erase(ord);
				}
			}
			ord = next_ord;
		}
	};
	StatusBar* action_panel = new StatusBar(make_action_orders);
	action_panel->SetBackground(engine->CreateBackgroungStatusBar_Action());
	return action_panel;
}
View* ViewCreator::CreateStatusBar(Engine* engine){
	// создание status bar
	Drawable* back_status_bar = engine->CreateBackgroungStatusBar();

	StatusBar* status_bar = new StatusBar([](StatusBar* status_bar){status_bar++;});
	status_bar->SetBackground(back_status_bar);
	StatusBar* amount_object = CreateStatusBar_Amount(engine);
	StatusBar* action_panel = CreateStatusBar_Action(engine);
	// Сборка всего в status_bar
	status_bar->AddView(amount_object);
	status_bar->AddView(action_panel);

	return status_bar;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Чтение из xml файла
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
View* ViewCreator::CreateView(const char* path) {
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile (path);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("View");
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml %s\n", path);
	return MakeView(root_node);
}

View* ViewCreator::MakeView(xml_node<>* root_node) {
	printf("Making a view\n");
	View* view = new View();
	for (xml_node<> * drawable_node = root_node->first_node("Drawable");
				drawable_node; drawable_node = drawable_node->next_sibling("Drawable")) {
		view->AddDrawable(MakeDrawable(drawable_node));
	}
	for (xml_node<> * view_node = root_node->first_node("View");
					view_node; view_node = view_node->next_sibling()) {
		view->AddView(MakeView(view_node));
	}
	printf("View is created\n");
	return view;
}

Drawable* ViewCreator::MakeDrawable(xml_node<>* node) {
	printf("Making a drawable\n");
	auto path = node->first_attribute("path")->value();
	auto width = atoi(node->first_attribute("width")->value());
	auto height = atoi(node->first_attribute("height")->value());
	auto x = atoi(node->first_attribute("x")->value());
	auto y = atoi(node->first_attribute("y")->value());
    printf("Read Drawable with path %s height %d width %d\n",
    	path,
    	width,
		height);
    SDL_Rect rect ={static_cast<Sint16>(x),static_cast<Sint16>(y),
    		static_cast<Uint16>(width), static_cast<Uint16>(height)};
    return new PlayingObject(rect, path);
}


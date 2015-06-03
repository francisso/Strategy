/*
 * ViewCreator.cpp
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#include "ViewCreator.h"

/**
 * Создание корневого view.
 * @param const char* board_path - путь к сохраненной игре
 */
View* ViewCreator::CreateMainView(Engine* engine, const char* board_path)
{
	View* main_view = new View();
	View* status_bar = CreateStatusBar(engine);
	View* game = CreateGame(engine, board_path);
	main_view->AddView(game);
	main_view->AddView(status_bar);
	return main_view;
}

/**
 * Создание view с полем боя
 */
View* ViewCreator::CreateGame(Engine* engine, const char* board_path){
	Drawable** texture = engine->LoadResources();
	GameField* field = FieldBuilder::CreateField();

	// создание game
	Uint16 w_game_window = static_cast<Uint16>(X_SIZE_WINDOW - 2*FRAME);
	Uint16 h_game_window = static_cast<Uint16>(Y_SIZE_WINDOW - HIGH_STATUS_BAR - 3*FRAME);
	SDL_Rect gameRect { FRAME, 2*FRAME, w_game_window, h_game_window};
	auto game = new Game(texture, field, gameRect);

	//создание игрока-человека
	HumanPlayer* Player_1=new HumanPlayer(1,RED,"Player 1");
	game->AddPlayer(Player_1);
	game->SwitchPlayer(1);

	//компьютерный игрок
	AI* Player_2=new AI(2,BLUE,"Computer 1");
	game->AddPlayer(Player_2);

	//Загрузка карты
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile (board_path);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("Game");
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	// Loading units from file
	for (xml_node<> * node = root_node->first_node("Unit");
					node; node = node->next_sibling("Unit")) {
			auto owner = atoi(node->first_attribute("owner")->value());
			auto x = atoi(node->first_attribute("x")->value());
			auto y = atoi(node->first_attribute("y")->value());
			auto bignore = false;
			if (!strcmp("true", node->first_attribute("bignore")->value()))
				bignore = true;
			UnitType type;
			auto s_type= node->first_attribute("type")->value();
			if (!strcmp("SWORDMAN", s_type)) {
				type = SWORDMAN;
			}
			else if (!strcmp("ARCHER", s_type)) {
				type = ARCHER;
			}
			game->Add(ObjectFactory::CreateUnit(type, owner), x,y, bignore);
		}
	// Loading buildings from file
	for (xml_node<> * node = root_node->first_node("Building");
						node; node = node->next_sibling("Building")) {
		auto owner = atoi(node->first_attribute("owner")->value());
		auto x = atoi(node->first_attribute("x")->value());
		auto y = atoi(node->first_attribute("y")->value());
		auto bignore = false;
		if (!strcmp("true", node->first_attribute("bignore")->value()))
			bignore = true;
		BuildingType type;
		auto s_type= node->first_attribute("type")->value();
		if (!strcmp("FORT", s_type)) {
			type = FORT;
		}
		else if (!strcmp("TOWER", s_type)) {
			type = TOWER;
		}
		game->Add(ObjectFactory::CreateBuilding(type, owner), x,y, bignore);
	}
	// Loading loot from file
	for (xml_node<> * node = root_node->first_node("Loot");
						node; node = node->next_sibling("Loot")) {
		auto x = atoi(node->first_attribute("x")->value());
		auto y = atoi(node->first_attribute("y")->value());
		auto bignore = false;
				if (!strcmp("true", node->first_attribute("bignore")->value()))
					bignore = true;
		LootType type;
		auto s_type= node->first_attribute("type")->value();
		if (!strcmp("GOLD", s_type)) {
			type = GOLD;
		}
		game->Add(ObjectFactory::CreateLoot(type), x,y, bignore);
	}
	// Loading environment objects from file
	for (xml_node<> * node = root_node->first_node("Environment");
						node; node = node->next_sibling("Environment")) {
		auto x = atoi(node->first_attribute("x")->value());
		auto y = atoi(node->first_attribute("y")->value());
		auto bignore = false;
				if (!strcmp("true", node->first_attribute("bignore")->value()))
					bignore = true;
		EnvironmentType type;
		auto s_type= node->first_attribute("type")->value();
		if (!strcmp("STONE", s_type)) {
			type = STONE;
		}
		else if (!strcmp("TREE", s_type)) {
			type = BRUSH;
		}
		game->Add(ObjectFactory::CreateEnvironment(type), x,y, bignore);
	}

	//Некоторые дополнительные объекты
	game->Add(ObjectFactory::CreateEnvironment(TREES),8,2);
	game->Add(ObjectFactory::CreateUnit(SWORDMAN,2),14,5);
	game->Add(ObjectFactory::CreateBuilding(FORT,2),14,0);
	return game;
}

/**
 * Создание прогресс бара
 */
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
						auto buiding_status_draw = new Draw(src, "res/images/buildings/castle.bmp");
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
						SDL_Rect src_text = {static_cast<Sint16>(15 + 130*i), 110, 110, 80};
						auto unit_status_draw = new Draw(src, "res/images/UI/unit_for_status_bar.bmp");
						unit_status_draw->SetX(static_cast<float>(20 + 130*i));
						unit_status_draw->SetY(20);
						StatusObject* unit_status = new StatusObject(unit_status_draw, src_text);
						char text[80];
						if (counters[i].unit_type == ARCHER)
							sprintf(text, "Archers %d", counters[i].amount);
						else if (counters[i].unit_type == SWORDMAN)
							sprintf(text, "Swordman %d", counters[i].amount);
						unit_status->SetText(text);
						unit_status->SetSizeText(16);
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
						auto button_status_draw = new Draw(src, "res/images/UI/button.bmp");
						button_status_draw->SetX(20);
						button_status_draw->SetY(20);
						Building* building = *ord->building;
						auto make_action = [building](SDL_Event* event){
							if (event->type == SDL_EventType::SDL_MOUSEBUTTONUP) {
									std::cout << "click on button\n";
									building->Produce(ARCHER);
							}
						};
						Button* button_status = new Button(button_status_draw, text_src, make_action);
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
StatusBar* ViewCreator::CreateStatusBar_Gold(Engine* engine){
	auto make_action_orders = [](StatusBar* status_bar){
		std::list<Order>::iterator next_ord;
		std::list<Order>::iterator ord = list_of_orders.begin();
		while ( ord != list_of_orders.end()) {
			next_ord = ++ord;
			ord--;
			if (ord->receiver == STATUS_BAR_GOLD){
				status_bar->ClearStatusObjects();
				SDL_Rect src_text = {30, 0, 20, 500};
				StatusObject* status_object = new StatusObject(nullptr, src_text);
				char text[200];
				int* gold = static_cast<int*>(ord->data);
				sprintf(text, "You are Billionaire!!! (%d)", *gold);
				status_object->SetText(text);
				status_object->SetColorText(255, 233, 127);
				status_object->SetSizeText(18);
				list_of_orders.erase(ord);
			}
			ord = next_ord;
		}
	};
	StatusBar* status_bar_gold = new StatusBar(make_action_orders);
	SDL_Rect src = {FRAME, FRAME, static_cast<Uint16>(X_SIZE_WINDOW - 2*FRAME), static_cast<Uint16>(FRAME)};
	status_bar_gold->SetBackground(engine->CreateRectangle(src, 95, 8, 46));
	return status_bar_gold;
}
View* ViewCreator::CreateStatusBar(Engine* engine){
	// создание status bar
	Drawable* back_status_bar = engine->CreateBackgroungStatusBar();

	StatusBar* status_bar = new StatusBar([](StatusBar* status_bar){status_bar++;});
	status_bar->SetBackground(back_status_bar);
	StatusBar* amount_object = CreateStatusBar_Amount(engine);
	StatusBar* action_panel = CreateStatusBar_Action(engine);
	StatusBar* status_bar_gold = CreateStatusBar_Gold(engine);
	// Сборка всего в status_bar
	status_bar->AddView(amount_object);
	status_bar->AddView(action_panel);
	status_bar->AddView(status_bar_gold);
	return status_bar;
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Чтение из xml файла
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
/**
 * Создание объекта view из xml файла
 */
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

/**
 * Создание объекта типа view из ноды xml файла
 */
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

/**
 * Создание объекта типа drawable из ноды xml файла
 */
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


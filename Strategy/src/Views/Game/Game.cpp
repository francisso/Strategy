/*
 * Game.cpp
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#include "Game.h"
#include <string>
#include <iostream>
#include <inttypes.h>

Game::Game(Drawable** texture, SDL_Rect windowRect) : Game(texture, new GameField(), windowRect) {
}

Game::Game(Drawable** texture, GameField* field, SDL_Rect windowRect) :
															WindowRect(windowRect),
															field(field),
															texture(texture) {
	x = 0;
	y = 0;
	cell_MouseX = 0;
	cell_MouseY = 0;
	cell_PickMouseX = 0;
	cell_PickMouseY = 0;
	PickMouse = false;
	Player* neu_player=new AI(0,GREY,"Neutral Player",NEUTRAL);
	players.push_back(neu_player);
	mainPlayer=neu_player;
}

Game::~Game()
{
	for (int i = 0; i < 4; i++)
		delete field->selection[i];
	delete field;
}

void Game::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const {
	float deltaX = WindowRect.x - x;
	float deltaY = WindowRect.y - y;
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++) {
		texture[field->grid[i][k].textureType]->SetX(static_cast<float>(CELL_X_PIXELS*i));
		texture[field->grid[i][k].textureType]->SetY(static_cast<float>(CELL_Y_PIXELS*k));
		f(texture[field->grid[i][k].textureType],deltaX, deltaY);
	}
	for (int i = 0;	i < CELL_X_NUMBER; i++)
	for (int k = 0;	k < CELL_Y_NUMBER; k++)
				f(field->grid[i][k].object, deltaX, deltaY);
	mainPlayer->DrawToScreen(f, deltaX, deltaY);
	if (PickMouse) {
		// выделение (много выделения)
		int min_x = (cell_PickMouseX < cell_MouseX) ? cell_PickMouseX : cell_MouseX;
		int min_y = (cell_PickMouseY < cell_MouseY) ? cell_PickMouseY : cell_MouseY;
		int max_x = (cell_PickMouseX > cell_MouseX) ? cell_PickMouseX : cell_MouseX;
		int max_y = (cell_PickMouseY > cell_MouseY) ? cell_PickMouseY : cell_MouseY;
		// сверху
		field->selection[HIGH]->SetY(static_cast<float>(min_y*CELL_Y_PIXELS));
		for (int i = min_x; i <= max_x; i++){
			field->selection[HIGH]->SetX(static_cast<float>(i*CELL_X_PIXELS));
			f(field->selection[HIGH], deltaX, deltaY);
		}
		// снизу
		field->selection[LOW]->SetY(static_cast<float>(max_y*CELL_Y_PIXELS));
		for (int i = min_x; i <= max_x; i++){
			field->selection[LOW]->SetX(static_cast<float>(i*CELL_X_PIXELS));
			f(field->selection[LOW], deltaX, deltaY);
		}
		// слева
		field->selection[LEFT]->SetX(static_cast<float>(min_x*CELL_X_PIXELS));
		for (int i = min_y; i <= max_y; i++){
			field->selection[LEFT]->SetY(static_cast<float>(i*CELL_Y_PIXELS));
			f(field->selection[LEFT], deltaX, deltaY);
		}
		// справа
		field->selection[RIGHT]->SetX(static_cast<float>(max_x*CELL_X_PIXELS));
		for (int i = min_y; i <= max_y; i++){
			field->selection[RIGHT]->SetY(static_cast<float>(i*CELL_Y_PIXELS));
			f(field->selection[RIGHT], deltaX, deltaY);
		}
	}
//	f(field->selection, deltaX, deltaY);
	this->View::Draw(f);
}

inline int Sign(bool isPositive) {
	return isPositive ? 1 : -1;
}

bool Game::ContainsCoordinates(Uint16 x, Uint16 y) const
{
	return (x >= WindowRect.x && y >= WindowRect.y &&
			x <= WindowRect.x + WindowRect.w && y <= WindowRect.y + WindowRect.h);
}

void Game::MotionMap(Time t)
{
	int X = 0, Y = 0;
	float delta = SpeedMap*t;
	float WindowW = static_cast<float>(WindowRect.w);
	float WindowH = static_cast<float>(WindowRect.h);
	SDL_GetMouseState(&X, &Y);
	// TODO убрать константу 5
	if (X < 5) {
		if (x >= delta)
			x -= delta;
		else x = 0;
	}
	if (Y < 5) {
		if (y >= delta)
			y -= delta;
		else y = 0;
	}
	if (X > X_SIZE_WINDOW - 5) {
		if (x < CELL_X_NUMBER*CELL_X_PIXELS - WindowW - delta)
			x += delta;
		else x = CELL_X_NUMBER*CELL_X_PIXELS - WindowW;
	}
	if (Y > Y_SIZE_WINDOW - 5) {
		if (y < CELL_Y_NUMBER*CELL_Y_PIXELS - WindowH - delta)
			y += delta;
		else y = CELL_Y_NUMBER*CELL_Y_PIXELS - WindowH;
	}
}


int Game::AddUnit(Unit* unit){
	int cell_x=static_cast<int>(unit->GetX()/CELL_X_PIXELS);
	int cell_y=static_cast<int>(unit->GetY()/CELL_Y_PIXELS);
	unit->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
	unit->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
	unit->SetDestX(unit->GetX());
	unit->SetDestY(unit->GetY());
	auto cell=&this->field->grid[cell_x][cell_y];
	if(cell->usedFor==NOTHING){
		cell->usedFor=CellType::OBJECT;
		cell->object=unit;
		return 0;
	}
	return 1;
}

int Game::AddUnitAtCell(Unit* unit, int cell_x, int cell_y) {
	if (cell_x < 0 || cell_y < 0 || cell_x >= CELL_X_NUMBER || cell_y >= CELL_Y_NUMBER)
		return 1;
	auto cell = &this->field->grid[cell_x][cell_y];
	if (cell->usedFor == CellType::NOTHING) {
		cell->usedFor = CellType::OBJECT;
		cell->object = unit;
		unit->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
		unit->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
		unit->SetDestX(unit->GetX());
		unit->SetDestY(unit->GetY());
		return 0;
	}
	//std::cout<<"GetX()t="<<unit->GetX()<<" ;GetY()="<<unit->GetY()<<" ;GetVirtualX()="<<unit->GetDestinationX()<<" ;GetVirtualY()="<<unit->GetDestinationY()<<std::endl;
	return 1;
}

int Game::AddBuilding(Building* building)
{
	int cell_x=static_cast<int>(building->GetX()/CELL_X_PIXELS);
	int cell_y=static_cast<int>(building->GetY()/CELL_Y_PIXELS);
	building->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
	building->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
	building->SetDestX(building->GetX());
	building->SetDestY(building->GetY());
	for(unsigned int i=0;i<building->GetSizeX();i++)
	for(unsigned int j=0;j<building->GetSizeY();j++)
	{
		if(field->grid[cell_x+i][cell_y+j].usedFor!=NOTHING) return 1;
	}
	for(unsigned int i=0;i<building->GetSizeX();i++)
	for(unsigned int j=0;j<building->GetSizeY();j++)
	{
		field->grid[cell_x+i][cell_y+j].usedFor=OBJECT_PART;
		field->grid[cell_x+i][cell_y+j].object=building;
		}
	field->grid[cell_x][cell_y].usedFor=OBJECT;
	return 0;
}

int Game::AddBuildingAtCell(Building* building, int cell_x, int cell_y){
	if (cell_x < 0 || cell_y < 0 || cell_x >= (CELL_X_NUMBER-static_cast<int>(building->GetSizeX())) || cell_y >= (CELL_Y_NUMBER-static_cast<int>(building->GetSizeY())))
		return 1;
	for(unsigned int i=0;i<building->GetSizeX();i++)
	for(unsigned int j=0;j<building->GetSizeY();j++)
	{
		if(field->grid[cell_x+i][cell_y+j].usedFor!=NOTHING) return 1;
	}
	for(unsigned int i=0;i<building->GetSizeX();i++)
	for(unsigned int j=0;j<building->GetSizeY();j++)
	{
		field->grid[cell_x+i][cell_y+j].usedFor=OBJECT_PART;
		field->grid[cell_x+i][cell_y+j].object=building;
		}
	field->grid[cell_x][cell_y].usedFor=OBJECT;

	building->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
	building->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
	building->SetDestX(building->GetX());
	building->SetDestY(building->GetY());
	return 0;
}
/*std::string Game::ActionOut(Action* action){
	std::string s;
	if(action->type==WAIT)
		s="STAY";
	if(action->type==MOVE_HORIZONTAL)
		s="MOVE_HORIZONTAL";
	if(action->type==MOVE_VERTICAL)
		s="MOVE_VERTICAL";
	return s;
}*/

int Game::AddPlayer(Player* newPlayer){
	for (unsigned int i=0;i<players.size();i++){
		if(players[i]->PlayerID==newPlayer->PlayerID) return 1;
	}
	players.push_back(newPlayer);
	return 0;
}

int Game::RemovePlayer(int ID){
	for(unsigned int i=0;i<players.size();i++){
		if(players[i]->PlayerID==ID){
			Player* player=players[i];
			players.erase(players.begin()+i);
			delete player;
			return 0;
		}
	}
	return 0;
}

int Game::SwitchPlayer(int ID){
	for(unsigned int i=0;i<players.size();i++){
		if(players[i]->PlayerID==ID){
			mainPlayer=players[i];
			std::cout<<"player switched to "<<mainPlayer->PlayerID<<std::endl;
			return 0;
		}
	}
	return 1;
}
void Game::TakeOrder(){
	auto it = vector_of_orders.begin();
	for ( ; it != vector_of_orders.end(); it++)
		if (it->receiver == GAME){
		}
}
/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Определение Game::Update
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */
void Game::Update(Time t) {
	MotionMap(t);
	TakeOrder();
	for(int i=0; i<CELL_X_NUMBER; i++)
	for(int k=0; k<CELL_Y_NUMBER; k++){
		if(field->grid[i][k].usedFor!=CellType::OBJECT)
			continue;
		switch(field->grid[i][k].object->GetObjectType()){
		case UNIT:
			UnitHandler(i,k,t);
			break;
		case BUILDING:
			StructureHandler(i,k,t);
			break;
		case LOOT:
			LootHandler(i,k,t);
			break;
		case ENVIRONMENT:
			EnvironmentHandler(i,k,t);
			break;
		}
	}
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Определение Game::OnEvent
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */
void Game::WorkWithPlayer(EventForPlayer* EventInfo, int cell_x, int cell_y, Uint8* keystates)
{
	GameObject* objectTarget = EventInfo->object;

	switch(mainPlayer->OnEvent(EventInfo)){
		case NOTHING_TO_DO:
			break;

		case PICK_OBJECT:
			break;
/*
			if (objectTarget==nullptr) {
				mainPlayer->FreePickedObjects();
				std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
				break;
			}
			if (objectTarget->GetObjectType() == UNIT || objectTarget->GetObjectType() == BUILDING) {
				PlayingObject *PlayObjectTarget = dynamic_cast<PlayingObject*>(objectTarget);
				if (PlayObjectTarget->GetOwnerID()==mainPlayer->PlayerID) {
					if (keystates[SDLK_LSHIFT] || keystates[SDLK_RSHIFT]) mainPlayer->AddPickedObject(PlayObjectTarget,false);
						else mainPlayer->AddPickedObject(PlayObjectTarget,true);
				}
			}

			std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
			break;
*/
		case MOVE_PICKED_TO:
			if (objectTarget!=nullptr) break;
			unsigned int i=0;
			std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
			while (i<mainPlayer->GetPickedNumber()) {
				PlayingObject* picked=mainPlayer->GetPicked(i);
				if (picked->GetObjectType()!=UNIT) break;
				Unit* unitPicked=dynamic_cast<Unit*>(picked);
				unitPicked->DirectMoveToCell(cell_x,cell_y,!(keystates[SDLK_LSHIFT] || keystates[SDLK_RSHIFT]));
				i++;
			}
			break;
	}
}

void Game::OnEvent(SDL_Event* event) {
	int X = static_cast<int>(x);
	int Y = static_cast<int>(y);
	Uint8* keystates=SDL_GetKeyState(NULL);
	if(event->type==SDL_MOUSEMOTION){
		cell_MouseX = (X + event->motion.x-WindowRect.x) / CELL_X_PIXELS;
		cell_MouseY = (Y + event->motion.y-WindowRect.y) / CELL_Y_PIXELS;
	} else
	if (event->type==SDL_MOUSEBUTTONDOWN) {
		if (event->button.button ==  SDL_BUTTON_LEFT) {
			PickMouse = true;
			cell_PickMouseX = (X + event->button.x-WindowRect.x) / CELL_X_PIXELS;
			cell_PickMouseY = (Y + event->button.y-WindowRect.y) / CELL_Y_PIXELS;
		}
	} else
	if (event->type==SDL_MOUSEBUTTONUP) {
		int cell_x=(X + event->button.x-WindowRect.x) / CELL_X_PIXELS;
		int cell_y=(Y + event->button.y-WindowRect.y) / CELL_Y_PIXELS;
		//TODO добавить новые инициализации при изменении структуры EventForPlayer
		EventForPlayer* EventInfo=new EventForPlayer();
		EventInfo->event=event;
		GameObject* objectTarget=field->grid[cell_x][cell_y].object;
		EventInfo->object=objectTarget;
		WorkWithPlayer(EventInfo, cell_x, cell_y, keystates);
		if (event->button.button ==  SDL_BUTTON_LEFT){
			PickMouse = false;
			int min_cell_x = (cell_PickMouseX < cell_MouseX) ? cell_PickMouseX : cell_MouseX;
			int min_cell_y = (cell_PickMouseY < cell_MouseY) ? cell_PickMouseY : cell_MouseY;
			int max_cell_x = (cell_PickMouseX > cell_MouseX) ? cell_PickMouseX : cell_MouseX;
			int max_cell_y = (cell_PickMouseY > cell_MouseY) ? cell_PickMouseY : cell_MouseY;
			if (!(keystates[SDLK_LSHIFT] || keystates[SDLK_RSHIFT]))
				mainPlayer->FreePickedObjects();
			for (int i = min_cell_x; i <= max_cell_x; i++)
			for (int k = min_cell_y; k <= max_cell_y; k++)
				if (field->grid[i][k].object != nullptr) {
					if (field->grid[i][k].object->GetObjectType() == UNIT ||
							field->grid[i][k].object->GetObjectType() == BUILDING){
						PlayingObject* play_object = dynamic_cast<PlayingObject*>(field->grid[i][k].object);
						if (play_object->GetOwnerID()==mainPlayer->PlayerID)
							mainPlayer->AddPickedObject(play_object, false);
					}
				}
			std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
		}
	} else
	if (event->type==SDL_KEYDOWN || event->type==SDL_KEYUP){
		EventForPlayer* EventInfo=new EventForPlayer();
		EventInfo->event=event;
		mainPlayer->OnEvent(EventInfo);
	}
}

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Определение Handler'ов
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

void Game::UnitHandler(int i, int k, Time t){
	Unit* unit=dynamic_cast<Unit*>(field->grid[i][k].object);
	//Action* action=unit->GetAction();
	float x=unit->GetX();
	float y=unit->GetY();
	float cell_x=static_cast<float>(CELL_X_PIXELS*i), cell_y=static_cast<float>(CELL_Y_PIXELS*k);
	//std::cout<<"x="<<x<<"; y="<<y<<"; cell_x="<<cell_x<<"; cell_y="<<cell_y<<std::endl;
	if(x==cell_x && y==cell_y){
		unit->NextAction();
		if(unit->GetAction()->type==WAIT){
			unit->SetDestX(unit->GetX());
			unit->SetDestY(unit->GetY());
		} else if (unit->GetAction()->type==MOVE){
			if(field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].usedFor==OBJECT || field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].usedFor==OBJECT_PART){
				if(field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].object->GetObjectType()==UNIT){
					if(dynamic_cast<Unit*>(field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].object)->GetAction()->type==MOVE){
						unit->RepeatLastAction();
						return;
					}
					if(dynamic_cast<Unit*>(field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].object)->GetAction()->type==WAIT){
						unit->ReduceTries();
						unit->RepeatLastAction();
						if(unit->GetTries()==0){
							unit->Stop();
							unit->RestoreTries();
						}
						return;
					}
				}
				return;
			} else if(field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].usedFor==NOTHING) {
				unit->RestoreTries();
				field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].usedFor=OBJECT;
				field->grid[i+unit->NextCellDirX()][k+unit->NextCellDirY()].object=unit;
				field->grid[i][k].usedFor=NOTHING;
				field->grid[i][k].object=nullptr;
			}
		}
	} else {
		x=x+t*unit->GetXSpeed();
		y=y+t*unit->GetYSpeed();
		Direction dir=unit->GetDirection();
		bool isHere=false;
		switch(dir){
		case NORTH:
			if(y<=cell_y) isHere=true;
			break;
		case NORTH_EAST:
			if(y<=cell_y && x>=cell_x) isHere=true;
			break;
		case EAST:
			if(x>=cell_x) isHere=true;
			break;
		case SOUTH_EAST:
			if(y>=cell_y && x>=cell_x) isHere=true;
			break;
		case SOUTH:
			if(y>=cell_y) isHere=true;
			break;
		case SOUTH_WEST:
			if(y>=cell_y && x<=cell_x) isHere=true;
			break;
		case WEST:
			if(x<=cell_x) isHere=true;
			break;
		case NORTH_WEST:
			if(y<=cell_y && x<=cell_x) isHere=true;
			break;
		}
		if(isHere){
			unit->SetX(cell_x);
			unit->SetY(cell_y);
		} else {
			unit->SetX(x);
			unit->SetY(y);
		}
	}
}

void Game::StructureHandler(int i, int k, Time t){
	if(i*k>0) return;
	if(t>0) return;
}

void Game::LootHandler(int i, int k, Time t){
	if(i*k>0) return;
	if(t>0) return;
}

void Game::EnvironmentHandler(int i, int k, Time t){
	if(i*k>0) return;
	if(t>0) return;
}

void Game::WritePointQueueInUnit(Unit* unit, std::queue<Point> &controlPoints)
{
	while(!controlPoints.empty())
	{
		Point currPoint=controlPoints.back();
		controlPoints.pop();
		unit->DirectMoveToCell(currPoint.x,currPoint.y,false);
	}
}

void Game::SendUnitTo(Unit* unit, int targetX, int targetY, bool replace)
{
	if(replace) unit->Stop();
	std::queue<Point> controlPoints;
	Point startPoint;
	startPoint.x=static_cast<int>(unit->GetDestX())/CELL_X_PIXELS;
	startPoint.y=static_cast<int>(unit->GetDestY())/CELL_Y_PIXELS;
	Point finishPoint;
	finishPoint.x=targetX;
	finishPoint.y=targetY;
	this->field->findPath(startPoint, finishPoint, controlPoints);
	WritePointQueueInUnit(unit, controlPoints);
}

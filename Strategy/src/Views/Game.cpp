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
	Player* neu_player=new AI(0,GREY,"Neutral Player",NEUTRAL);
	players.push_back(neu_player);
	mainPlayer=neu_player;
}

void Game::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const {
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++) {
		texture[field->grid[i][k].textureType]->SetX(static_cast<float>(CELL_X_PIXELS*i));
		texture[field->grid[i][k].textureType]->SetY(static_cast<float>(CELL_Y_PIXELS*k));
		f(texture[field->grid[i][k].textureType], WindowRect.x - x, WindowRect.y - y);
	}
	for (int i = 0;	i < CELL_X_NUMBER; i++)
	for (int k = 0;	k < CELL_Y_NUMBER; k++)
				f(field->grid[i][k].object, WindowRect.x - x, WindowRect.y - y);
	f(field->selection, WindowRect.x - x, WindowRect.y - y);
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
	auto cell=&this->field->grid[cell_x][cell_y];
	if(cell->objectType==NOTHING){
		cell->objectType=CellType::UNIT;
		cell->object=unit;
		return 0;
	}
	return 1;
}

int Game::AddUnitAtCell(Unit* unit, int cell_x, int cell_y) {
	if (cell_x < 0 || cell_y < 0 || cell_x >= CELL_X_NUMBER || cell_y >= CELL_Y_NUMBER)
		return 1;
	auto cell = &this->field->grid[cell_x][cell_y];
	if (cell->objectType == CellType::NOTHING) {
		cell->objectType = CellType::UNIT;
		cell->object = unit;
		return 0;
	}
	//std::cout<<"GetX()t="<<unit->GetX()<<" ;GetY()="<<unit->GetY()<<" ;GetVirtualX()="<<unit->GetDestinationX()<<" ;GetVirtualY()="<<unit->GetDestinationY()<<std::endl;
	return 1;
}




std::string Game::ActionOut(Action* action){
	std::string s;
	if(action->type==STAY)
		s="STAY";
	if(action->type==MOVE_HORIZONTAL)
		s="MOVE_HORIZONTAL";
	if(action->type==MOVE_VERTICAL)
		s="MOVE_VERTICAL";
	return s;
}

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

/**
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 *
 * Определение Game::Update
 *
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */
void Game::Update(Time t) {
	MotionMap(t);
	Action* action;
	Unit* unit;
	for (int i = 0; i < CELL_X_NUMBER; i++)
	for (int k = 0; k < CELL_Y_NUMBER; k++) {
		//Пока что осуществляем действия только для юнитов
		if (field->grid[i][k].objectType != CellType::UNIT)
			continue;
		unit=dynamic_cast<Unit*>(field->grid[i][k].object);
		action = unit->GetAction();
		//std::cout<<"ActionType is "<<ActionOut(action)<<std::endl;
		if (action->type==STAY){
			unit->SetDestinationX(unit->GetX());
			unit->SetDestinationY(unit->GetY());
			unit->NextAction();
			//std::cout<<unit->GetVirtualX()<<"=GetVirtualX()=GetX()="<<unit->GetX()<<std::endl;
		}
		if (action->type==MOVE_VERTICAL){
			//auto x = unit->GetX();
			auto y = unit->GetY();
			if(y==CELL_Y_PIXELS*k){
				//auto xNext = k + ((action->IsPositive) ? 1 : -1);
				if(field->grid[i][k+Sign(action->isPositive)].objectType==CellType::NOTHING){
					field->grid[i][k+Sign(action->isPositive)].objectType=CellType::OCCUPIED;
					unit->SetY(y+t*unit->GetSpeed()*static_cast<float>(Sign(action->isPositive)));
				} else if (field->grid[i][k+Sign(action->isPositive)].objectType==CellType::UNIT){
					if(dynamic_cast<Unit*>(field->grid[i][k+Sign(action->isPositive)].object)->GetAction()->type==STAY) unit->StopUnitHard();
					continue;
				} else if (field->grid[i][k+Sign(action->isPositive)].objectType==CellType::BUILDING){
					unit->StopUnitHard();
					continue;
				}
			} else {
				if((y+t*unit->GetSpeed())>=CELL_Y_PIXELS*(k+1) || (y-t*unit->GetSpeed())<=CELL_Y_PIXELS*(k-1)){
					int y_next = k+Sign(action->isPositive);
					field->grid[i][y_next].objectType = CellType::UNIT;
					field->grid[i][y_next].object = unit;
					field->grid[i][k].objectType = CellType::NOTHING;
					field->grid[i][k].object = nullptr;
					unit->SetY(static_cast<float>(CELL_Y_PIXELS*y_next));
					unit->NextAction();
					//std::cout<<"ActionType is "<<ActionOut(unit->GetAction())<<std::endl;
				} else {
					unit->SetY(y+t*unit->GetSpeed()*static_cast<float>(Sign(action->isPositive)));
				}
			}
		}
		if (action->type==MOVE_HORIZONTAL){
			auto x=unit->GetX();
			if(x==CELL_X_PIXELS*i){
				if(field->grid[i+Sign(action->isPositive)][k].objectType==CellType::NOTHING){
					field->grid[i+Sign(action->isPositive)][k].objectType=CellType::OCCUPIED;
					unit->SetX(x+t*unit->GetSpeed()*static_cast<float>(Sign(action->isPositive)));
				} else if (field->grid[i+Sign(action->isPositive)][k].objectType==CellType::UNIT){
					if(dynamic_cast<Unit*>(field->grid[i+Sign(action->isPositive)][k].object)->GetAction()->type==STAY) unit->StopUnitHard();
					continue;
				} else if (field->grid[i+Sign(action->isPositive)][k].objectType==CellType::BUILDING){
					unit->StopUnitHard();
					continue;
				}
			} else {
				if((x+t*unit->GetSpeed())>=CELL_Y_PIXELS*(i+1) || (x-t*unit->GetSpeed())<=CELL_Y_PIXELS*(i-1)){
					int x_next = i+Sign(action->isPositive);
					field->grid[x_next][k].objectType = CellType::UNIT;
					field->grid[x_next][k].object = unit;
					field->grid[i][k].objectType = CellType::NOTHING;
					field->grid[i][k].object = nullptr;
					unit->SetX(static_cast<float>(x_next*CELL_X_PIXELS));
					unit->NextAction();
				} else {
					unit->SetX(x+t*unit->GetSpeed()*static_cast<float>(Sign(action->isPositive)));
				}
			}
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
void Game::OnEvent(SDL_Event* event) {
	int X = static_cast<int>(x);
	int Y = static_cast<int>(y);
	Uint8* keystates=SDL_GetKeyState(NULL);
	if(event->type==SDL_MOUSEMOTION){
		int cell_x=(X + event->motion.x-WindowRect.x) / CELL_X_PIXELS;
		int cell_y=(Y + event->motion.y-WindowRect.y) / CELL_Y_PIXELS;
		field->selection->SetX(static_cast<float>(cell_x*CELL_X_PIXELS));
		field->selection->SetY(static_cast<float>(cell_y*CELL_Y_PIXELS));
	} else
	if (event->type==SDL_MOUSEBUTTONDOWN) {
		int cell_x=(X + event->button.x-WindowRect.x) / CELL_X_PIXELS;
		int cell_y=(Y + event->button.y-WindowRect.y) / CELL_Y_PIXELS;
		GameObject* objectTarget=field->grid[cell_x][cell_y].object;
		EventForPlayer* EventInfo=new EventForPlayer();
		EventInfo->event=event;
		EventInfo->object=objectTarget;
		//TODO добавить новые инициализации при изменении структуры EventForPlayer
		switch(mainPlayer->OnEvent(EventInfo)){
		case NOTHING_TO_DO:
			break;
		case PICK_OBJECT:
			if(objectTarget==nullptr){
				mainPlayer->FreePickedObjects();
				std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
				break;
			}
			if (objectTarget->GetObjectType() == UNIT_1) {
				PlayingObject *PlayObjectTarget = dynamic_cast<PlayingObject*>(objectTarget);
				if(PlayObjectTarget->GetOwnerID()==mainPlayer->PlayerID){
					if(keystates[SDLK_LSHIFT] || keystates[SDLK_RSHIFT]) mainPlayer->AddPickedObject(PlayObjectTarget,false);
						else mainPlayer->AddPickedObject(PlayObjectTarget,true);
				}
			}

			std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
			break;
		case MOVE_PICKED_TO:
			if(objectTarget!=nullptr) break;
			unsigned int i=0;
			std::cout<<"Number of picked is "<<mainPlayer->GetPickedNumber()<<std::endl;
			while(i<mainPlayer->GetPickedNumber()){
				PlayingObject* picked=mainPlayer->GetPicked(i);
				if(picked->GetObjectType()!=UNIT_1) break;
				Unit* unitPicked=dynamic_cast<Unit*>(picked);
				unitPicked->DirectMoveToCell(cell_x,cell_y,true);
				i++;
			}
			break;
		}
	} else
	if (event->type==SDL_KEYDOWN || event->type==SDL_KEYUP){
		EventForPlayer* EventInfo=new EventForPlayer();
		EventInfo->event=event;
		mainPlayer->OnEvent(EventInfo);
	}

}

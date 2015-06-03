/*
 * Player.h
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#ifndef PLAYERS_PLAYER_H_
#define PLAYERS_PLAYER_H_

#include <list>
#include <string>
#include <functional>

#include "../Constants.h"
#include "SDL/SDL.h"

#include "../Drawable/GameObjects/Building.h"
#include "../Views/Order.h"

struct EventForPlayer{
	SDL_Event* event;
	GameObject* object;
	//TODO проверить на дополнительные параметры, поставленные к передаче
};

enum Color{GREY,RED,BLUE,GREEN,YELLOW,ORANGE,CYAN,BROWN,PURPLE};

enum TaskForGame{NOTHING_TO_DO,PICK_OBJECT,MOVE_PICKED_TO};
// сообщения, например для строки состояния
extern std::list<Order> list_of_orders;

/**
 * Класс, реализующий интерфейс игрока
 */
class Player {
	public:
		const int PlayerID;
		Player(int ID,Color playerColor=GREY);
		virtual ~Player();

		/**
		 * @AddPickedUnit добавляет @unit в @chosenUnits
		 * если @replace имеет значение true, то сначала @chosenUnits очистится и тогда @unit окажется единственным в @chosenUnits
		 */
		void AddPickedObject(PlayingObject* object, bool replace=true);

		/**
		 * @GetFirstPicked возвращает указатель на первый выбранный юнит (может быть единственным)
		 */
		PlayingObject* GetPicked(unsigned int number);

		/**
		 * @GetPickedNumber возвращает число выбранных объектов
		 */
		unsigned int GetPickedNumber();

		/**
		 * @FreePickedObjects освобождает массив выбранных объектов
		 */
		void FreePickedObjects();

		/**
		 * обработка действий, переданных из Game
		 */
		virtual TaskForGame OnEvent(EventForPlayer* eventInfo) =0;

		/**
		 * изменяет Gold на величину @income
		 * @return возвращает 0 если после вызова метода @Gold больше или равно нулю
		 *         возвращает 1 если поле вызова метода @Gold должно оказаться меньше нуля; уменьшения Gold в этом слуае не происходит
		 */
		int AddGold(int income, bool toZero=false);

		/**
		 * @return количества золота этого игрока
		 */
		int GetGold();

		std::string GetSignature();
		void SetSignature(std::string newSig);

		Color GetColor();
		void SetColor(Color newColor);
		/**
		 * @DrawToScreen рисует выделение выбранных объектов
		 */
		void DrawToScreen(std::function<void (Drawable*, float X0, float Y0)> f,
								float deltaX, float deltaY) const;

		//bool IsShiftPressed();
		//void SetShiftPressed(bool);
		// обновление выделенных объектов в строке состояния
		void UpdateStatusBar_selected();
		void UpdateStatusBar_Gold();

	protected:
		int playerGold;
		std::vector<PlayingObject*> pickedObjects;
		Color playerColor;
		std::string playerSignature;
		Draw* selection;
		Draw* selectionBuilding;
		std::vector<AmountOfUnit> counter;
		Building* building;// последнее выделенное здание
		Draw* health[4];
		//bool ShiftPressed;
};

/**
 * возвращает string с названием цвета @color
 */
std::string ColorToString(Color color);

#endif /* PLAYERS_PLAYER_H_ */

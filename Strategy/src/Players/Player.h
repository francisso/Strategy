/*
 * Player.h
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#ifndef PLAYERS_PLAYER_H_
#define PLAYERS_PLAYER_H_

#include <vector>
#include <string>

#include "../GameObject.h"
#include "../Constants.h"
#include "SDL/SDL.h"

struct EventForPlayer{
	SDL_Event* event;
	GameObject* object;
	//TODO проверить на дополнительные параметры, поставленные к передаче
};

enum Color{GREY,RED,BLUE,GREEN,YELLOW,ORANGE,CYAN,BROWN,PURPLE};

enum TaskForGame{NOTHING_TO_DO,PICK_OBJECT,MOVE_PICKED_TO};

/**
 * Класс, реализующий интерфейс игрока
 */
class Player {
	public:
		const int PlayerID;
		Player(int ID,Color playerColor=GREY);
		virtual ~Player()=default;

		/**
		 * @AddPickedUnit добавляет @unit в @chosenUnits
		 * если @replace имеет значение true, то сначала @chosenUnits очистится и тогда @unit окажется единственным в @chosenUnits
		 */
		void AddPickedObject(GameObject* object, bool replace=true);

		/**
		 * @GetFirstPicked возвращает указатель на первый выбранный юнит (может быть единственным)
		 */
		GameObject* GetFirstPicked();

		/**
		 * @GetPickedNumber возвращает число выбранных объектов
		 */
		unsigned int GetPickedNumber();

		/**
		 * обработка действий, переданных из Game
		 */
		virtual TaskForGame OnEvent(EventForPlayer* eventInfo) =0;

		/**
		 * изменяет Gold на величину @income
		 * @return возвращает 0 если после вызова метода @Gold больше или равно нулю
		 *         возвращает 1 если поле вызова метода @Gold должно оказаться меньше нуля; уменьшения Gold в этом слуае не происходит
		 */
		int AddGold(int income);

		/**
		 * @return количества золота этого игрока
		 */
		int GetGold();

		std::string GetSignature();
		void SetSignature(std::string newSig);

		Color GetColor();
		void SetColor(Color newColor);

	protected:
		int playerGold;
		std::vector<GameObject*> pickedObjects;
		Color playerColor;
		std::string playerSignature;
};

/**
 * возвращает string с названием цвета @color
 */
std::string ColorToString(Color color);

#endif /* PLAYERS_PLAYER_H_ */

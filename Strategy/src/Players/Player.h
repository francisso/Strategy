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

#include "../Units/Unit.h"
#include "../Constants.h"
#include "SDL/SDL.h"

struct EventForPlayer{
	SDL_Event* event;
	int cell_x;
	int cell_y;
	Unit* unit;
	//TODO проверить на дополнительные параметры, поставленные к передаче
};

enum Color{GREY,RED,BLUE,GREEN,YELLOW,ORANGE,CYAN,BROWN,PURPLE};

enum TaskForGame{NOTHING_TO_DO,PICK,MOVE_PICKED_TO};

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
		void AddPickedUnit(Unit* unit, bool replace=true);

		/**
		 * обработка действий, переданных из Game
		 */
		virtual void OnEvent(EventForPlayer* eventInfo);

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
		std::vector<Unit*> chosenUnits;
		Color playerColor;
		std::string playerSignature;
		TaskForGame task;
};

/**
 * возвращает string с названием цвета @color
 */
std::string ColorToString(Color color);

#endif /* PLAYERS_PLAYER_H_ */

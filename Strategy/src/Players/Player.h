/*
 * Player.h
 *
 *  Created on: Apr 3, 2015
 *      Author: staslatgttt
 */

#ifndef PLAYERS_PLAYER_H_
#define PLAYERS_PLAYER_H_

#include <vector>

#include "../Units/Unit.h"
#include "../Constants.h"

/**
 * Класс, реализующий интерфейс игрока
 */
class Player {
	protected:
		int Gold;
		std::vector<Unit*> chosenUnits;
	public:
		const int PlayerID;
		Player(int ID);
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
};



#endif /* PLAYERS_PLAYER_H_ */

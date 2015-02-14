/*
 * Game.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#ifndef THREAD_H_
#define THREAD_H_

#include <thread>
#endif

#include "Engine.h"
#include "GameField.h"

//Основной класс игры
//Организует логику остальных классов
class Game {
public:
	Game();
	virtual ~Game();
	void Start();
private:
	struct ToDraw {
			Engine* engine;
			GameField* gameField;
		} toDraw;

	//Constructor initializes all the resources
	void LoadResources();
	//Destructor frees resources
	void FreeResources();
	//Вычисляет, сколько времени прошло с последнего такта
	//И обновляет положения всех объектов
	void thread_Update();

	void thread_Draw(ToDraw toDraw);






	GameField* gameField;
};

#endif /* GAME_H_ */

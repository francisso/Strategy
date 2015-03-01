/*
 * Game.h
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#include <functional>

#include "../Drawable.h"
#include "View.h"

//Окно, отображающее игровое поле
// и отрабатывающее логику самой игры
//  (атака 1 юнита на другой, например)
class Game: public View {
public:
	Game(Drawable* Background);
	virtual ~Game();

private:
	GameField* field;
	Drawable* background;
	virtual void Draw(std::function<void (Drawable*)> f);
	virtual void Update(Time t);
};

#endif /* GAME_H_ */
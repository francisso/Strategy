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
#include "../Constants.h"

//Окно, отображающее игровое поле
// и отрабатывающее логику самой игры
//  (атака 1 юнита на другой, например)
class Game: public View {
public:
	Game(Drawable* Background);
	Game(Drawable* background, GameField* field);
	virtual ~Game()=default;
	void AddUnitAtCell(Unit* unit, int cell_x, int cell_y);
	virtual void OnEvent(SDL_Event* event);
	std::string ActionOut(Action* action);
private:
	GameField* field;
	Drawable* background;
	virtual void Draw(std::function<void (Drawable*)> f);
	virtual void Update(Time t);
};

#endif /* GAME_H_ */

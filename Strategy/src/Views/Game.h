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
	Game(Drawable** texture);
	Game(Drawable** texture, GameField* field);
	virtual ~Game()=default;
	//TODO !!! добавить документацию по всем функциям.
	//(описание, описание параметров, описание возвращаемого значения)
	void AddUnitAtCell(Unit* unit, int cell_x, int cell_y);
	virtual void OnEvent(SDL_Event* event);
	std::string ActionOut(Action* action);
private:
	CoordinateType x;
	CoordinateType y;
	const CoordinateType SpeedMap = 20.0f;
	GameField* field;
	Drawable** texture;
	virtual void Draw(std::function<void (Drawable*, CoordinateType X0, CoordinateType Y0)> f) const;
	virtual void Update(Time t);
	void MotionMap(Time t);
};

#endif /* GAME_H_ */

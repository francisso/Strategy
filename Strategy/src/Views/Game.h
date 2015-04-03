/*
 * Game.h
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#include <functional>
#include <fstream>

#include "../Drawable.h"
#include "View.h"
#include "../Constants.h"

// Размеры окна
extern CoordinateType X_SIZE_WINDOW;
extern CoordinateType Y_SIZE_WINDOW;
//Окно, отображающее игровое поле
// и отрабатывающее логику самой игры
//  (атака 1 юнита на другой, например)
class Game: public View {
public:
	Game(Drawable** texture);
	Game(Drawable** texture, GameField* field);
	virtual ~Game()=default;
	virtual void OnEvent(SDL_Event* event);

	const char* DefaultMapPath = "res/maps/mapSaved";
private:
	CoordinateType x;
	CoordinateType y;
	const CoordinateType SpeedMap = 20.0f;
	GameField* field;
	Drawable** texture;
	virtual void Draw(std::function<void (Drawable*, CoordinateType X0, CoordinateType Y0)> f) const;
	virtual void Update(Time t);
	//передвижение карты :
	// изменяет облать карты которая отображается на экран
	// проверяя координаты мыши
	void MotionMap(Time t);
	void SaveMap (const char* path);
	int Getline(std::string* line, GameField* field);
};

#endif /* GAME_H_ */

/*
 * View.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <vector>

#include "Types.h"
#include "GameField.h"


//Класс окна, отображающегося на экране
class View {
public:
	View();
	virtual ~View();

	//Функции, к которым обращается Engine
	// для отрисовки окна
	//Engine вызывает Draw с функцией, отрисовывающей Drawable
	// и мы применяем эту функцию ко всем Drawable этого класса
	template <class UnaryFunction>
	void Draw(UnaryFunction f);

	//Функции, к которым обращается Engine
	// при клику
	virtual void onClick(SDL_Event event);

	//Обновить по плану положения - состояния всего
	// t - время, прошедшее с последнего вызова
	virtual void UpdatePosition(Time t);

private:
	//Ссылки на другие View
	std::vector<View*> views;
	//Игровое поле
	GameField* gameField = nullptr;
	//Размеры этого view
	CoordinateType x;
	CoordinateType y;
	CoordinateType height;
	CoordinateType width;

	//Картинка самого View
	GameObject* background;

};

#endif /* VIEW_H_ */

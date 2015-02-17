/*
 * View.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <vector>
#include <functional>
#include <SDL/SDL.h>

#include "Types.h"
#include "GameField.h"
#include "GameObject.h"
#include "Drawable.h"


//Класс окна, отображающегося на экране
class View {
public:
	View();
	virtual ~View();

	//Функции, к которым обращается Engine
	// для отрисовки окна
	//Engine вызывает Draw с функцией, отрисовывающей Drawable
	// и мы применяем эту функцию ко всем Drawable этого класса
	virtual void Draw(std::function<void (Drawable*)> f);

	//Функции, к которым обращается Engine
	// в случае события
	virtual void onEvent(SDL_Event event);

	virtual void Update(Time t);


	//Функции для составления view
	void AddText(char* text, CoordinateType x, CoordinateType y, int size);

	void SetImage(Drawable* image);

	void AddView(View* view, CoordinateType x, CoordinateType y);

	void AddDrawable(Drawable* drawable);

private:
	//То, что view отображает
	std::vector<View*> views;
	std::vector<Drawable*> drawables;

	//Фоновое изображение для данного View.
	Drawable* image;
};

#endif /* VIEW_H_ */

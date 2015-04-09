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
#include <inttypes.h>

#include "../Drowable/GameObjects/PlayingObject.h"
#include "../Drowable/GameObjects/Units/Unit.h"
#include "../Types.h"
#include "GameField.h"
#include "../IDrawable.h"


//Класс окна, отображающегося на экране
class View {
public:
	View()=default;
	virtual ~View()=default;

	//Функции, к которым обращается Engine
	// для отрисовки окна
	//Engine вызывает Draw с функцией, отрисовывающей Drawable
	// и мы применяем эту функцию ко всем Drawable этого класса
	virtual void Draw(std::function<void (Drawable*, CoordinateType X0, CoordinateType Y0)> f) const;

	//Функции, к которым обращается Engine
	// в случае события
	virtual void OnEvent(SDL_Event* event);

	virtual void Update(Time t);

	//Функции для составления view
	void SetImage(Drawable* image);

	void AddView(View* view);

	void AddDrawable(Drawable* drawable);

	//returns true если координаты принадлежат этому view
	virtual bool ContainsCoordinates(Uint16 x, Uint16 y) const;

private:
	//То, что view отображает
	std::vector<View*> views;
	std::vector<Drawable*> drawables;

	//Фоновое изображение для данного View.
	Drawable* image = nullptr;
};

#endif /* VIEW_H_ */

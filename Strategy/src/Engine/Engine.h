/*
 * Engine.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_



#include "../Views/View.h"

class Engine {
public:
	Engine();
	virtual ~Engine();

	//Устанавливаем окно, которое будет отображаться
	void SetView(View* view) {this->view = view;};

	//Начинаем рутину (все потоки запсукаются)
	void Run();

private:

	//Активное окно
	View* view;
	SDL_Surface* screen;

	//Constructor initializes all the resources
	void LoadResources();
	//Destructor frees resources
	void FreeResources();
	//Вычисляет, сколько времени прошло с последнего такта
	//И обновляет положения всех объектов
	void thread_Update();
	//Постоянно отрисовывает игровое поле
	// - toDraw - локальный член класса
	void thread_Draw(View view);
	//Поток, обрабатывающий ввод
	void thread_Input(View* view);

	//Отрисовывает окно
	void DrawView(View view);
	void Draw(Drawable* drawable);

};
#endif /* ENGINE_ENGINE_H_ */

/*
 * Engine.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include "EngineGraphic.h"
#include "EngineInput.h"

#include "../View.h"

class Engine {
public:
	Engine();
	virtual ~Engine();

	//Устанавливаем окно, которое будет отображаться
	void SetView(View* view) {this->view = view;};

	//Начинаем рутину (все потоки запсукаются)
	void Run();

private:

	struct ToDraw {
		EngineGraphic* graphic;
		View* view;
	} toDraw;


	//Классы, сожержащие функции вывода изображений
	// и первичной обработки ввода
	EngineGraphic* graphics;
	EngineInput* input;
	//Активное окно
	View* view;


	//Constructor initializes all the resources
	void LoadResources();
	//Destructor frees resources
	void FreeResources();
	//Вычисляет, сколько времени прошло с последнего такта
	//И обновляет положения всех объектов
	void thread_Update();
	//Постоянно отрисовывает игровое поле
	// - toDraw - локальный член класса
	void thread_Draw(ToDraw toDraw);
	//Поток, обрабатывающий ввод
	void thread_Input(View* view);



};
#endif /* ENGINE_ENGINE_H_ */

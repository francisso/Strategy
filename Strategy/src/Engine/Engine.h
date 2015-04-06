/*
 * Engine.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <exception>
#include <thread>
#include <time.h>

#include "../Constants.h"
#include "../Views/View.h"
#include "../Views/GameField.h"

// Размеры окна
extern float X_SIZE_WINDOW;
extern float Y_SIZE_WINDOW;

class Engine {
public:
	Engine();
	virtual ~Engine();

	//Устанавливаем окно, которое будет отображаться
	void SetView(View* view) {this->view = view;};

	//Начинаем рутину (все потоки запсукаются)
	void Run();

	// создание карты
	Drawable* CreateBackgroung(GameField* field) const;

	//Constructor initializes all the resources
	Drawable** LoadResources();
	//Destructor frees resources
	void FreeResources();

private:
	//Выполняем многопоточно или используем игровой цикл
//TODO check multithreading
	const bool MULTUTHREADING = false;
	///Запускаьт ли игру в полноэкранном режиме?
	//возможно, const надо будет убрать.
	const bool FULLSCREEN = false;
	bool game_is_running = true;
	//FPS для многопоточного исполнения
	static const int DRAW_FPS = 300;
	static const int UPDATE_FPS = 300;

	//Активное окно
	View* view;
	SDL_Surface* screen;
	Drawable* texture[6];

	//Вычисляет, сколько времени прошло с последнего такта
	//И обновляет положения всех объектов
	static void ThreadUpdate(View* view);
	//Постоянно отрисовывает игровое поле
	// - toDraw - локальный член класса
	static void ThreadDraw(View* view, SDL_Surface* screen);
	//Поток, обрабатывающий ввод
	static void ThreadInput(View* view);

	//Отрисовывает окно
	static void DrawView(View* view, SDL_Surface* screen);
	static void Draw(Drawable* drawable, SDL_Surface* screen, float X0 = 0, float Y0 = 0);

	void ProcessInput(View* view);
	void GameCycle();
};
#endif /* ENGINE_ENGINE_H_ */

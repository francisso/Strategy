/*
 * Game.h
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#include <functional>

#include "View.h"
#include "../Constants.h"
#include "../IDrawable.h"
#include "../Players/Player.h"
#include "../Players/AI.h"
//#include "../Players/HumanPlayer.h"
//#include "../Types.h"

// Размеры окна
extern float X_SIZE_WINDOW;
extern float Y_SIZE_WINDOW;

//Окно, отображающее игровое поле
// и отрабатывающее логику самой игры
//  (атака 1 юнита на другой, например)
class Game: public View {
public:
	Game(Drawable** texture, SDL_Rect windowRect);
	Game(Drawable** texture, GameField* field, SDL_Rect windowRect);
	virtual ~Game();

	/**
	 * @AddUnit добавляет @unit на игровое поле согласно его координатам
	 * @return 0, если добавление успешно произведено
	 *          1 если невозможно добавить (например, клетка занята другим юнитом)
	 */
	int AddUnit(Unit* unit);

	/**
	 * @AddUnitAtCell делает то же самое, что и @AddUnit, но не приводит координаты @unit к координатам клетки
	 * также возможны баги из-за полного несоответствия вручную введенных координат ячейки и координат @unit
	 * лучше ее вообще не использовать и удалить из проекта
	 */
	int AddUnitAtCell(Unit* unit, int cell_x, int cell_y);
	virtual void OnEvent(SDL_Event* event);
	std::string ActionOut(Action* action);

	/**
	 * Добавляет нового игрока
	 * @return возвращает 0, если игрок успешно добавлен
	 *         возвращает 1, если не удалось по каким-то причинам создать игрока
	 */
	int AddPlayer(Player* newPlayer);

	/**
	 * Удаляет игрока с заданным ID
	 * @return 0, если игрок успешно удален
	 *         1, если не удалось по каким-то причинам удалить игрока
	 */

	int RemovePlayer(int ID);

	/**
	 * меняет @mainPlayer на заданный по @ID
	 * @return 0 если игрок успешно заменен
	 *         1 если игрока с таким @PlayerID не существует или @ID==0 (PlayerID нейтрального игрока)
	 */
	int SwitchPlayer(int ID);
private:
	float x;
	float y;
	//координаты клетки мыши
	int cell_MouseX;
	int cell_MouseY;
	// координаты клетки, где была нажата мышь
	int cell_PickMouseX;
	int cell_PickMouseY;
	// нажата ли мышь
	bool PickMouse;
	// прямоугольник где будет рисоваться Game
	SDL_Rect WindowRect;
	const float SpeedMap = 20.0f;
	GameField* field;
	Drawable** texture;
	virtual void Draw(std::function<void (Drawable*, float X0, float Y0)> f) const;
	virtual void Update(Time t);
	virtual bool ContainsCoordinates(Uint16 x, Uint16 y) const;
	void WorkWithPlayer(EventForPlayer* EventInfo, int cell_x, int cell_y);
	//передвижение карты :
	// изменяет облать карты которая отображается на экран
	// проверяя координаты мыши
	void MotionMap(Time t);
	//массив указателей на игроков
	std::vector<Player*> players;
	//указатель на игрока, которому будут переданы любые события
	Player* mainPlayer;

	void UnitHandler(int i, int k, Time t);
	void StructureHandler(int i, int k, Time t);
	void LootHandler(int i, int k, Time t);
	void EnvironmentHandler(int i, int k, Time t);

	bool UnitActionPossibility(int i, int k, Unit* unit);
};

#endif /* GAME_H_ */

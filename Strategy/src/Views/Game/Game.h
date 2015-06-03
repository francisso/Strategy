/*
 * Game.h
 *
 *  Created on: 15 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAME_H_
#define GAME_H_

#include <functional>
#include <list>

#include "../View.h"
#include "../../Constants.h"
#include "../../Drawable/GameObjects/Building.h"
#include "../../IDrawable.h"
#include "../../Players/Player.h"
#include "../../Players/AI.h"
//#include "../Players/HumanPlayer.h"
#include "../../Types.h"
#include "../../Drawable/GameObjects/ObjectFactory.h"

// Размеры окна
extern float X_SIZE_WINDOW;
extern float Y_SIZE_WINDOW;
// приказы
extern std::list<Order> list_of_orders;

//Окно, отображающее игровое поле
// и отрабатывающее логику самой игры
//  (атака 1 юнита на другой, например)
class Game: public View {
public:
	Game(Drawable** texture, SDL_Rect windowRect);
	Game(Drawable** texture, GameField* field, SDL_Rect windowRect);
	virtual ~Game();

	/**
	 * Удаляет любой объект, который занимает клетку
	 * Если клетка занята частью объекта типа Sizeable, будут очищены также все клетки, принадлежавшие этому объекту
	 */
	int CleanFromObjects(int cell_x, int cell_y);

	/**
	 * Добавляет @newObject на GameField
	 * Если @cell_x и @cell_y отрицательные или больше размеров карты, будут использованы собственные координаты @newObject
	 * Если и они не подходят по параметрам, будет совершена попытка поставить @newObject в клетку (0,0)
	 * При 	@ignore=true юнит будет помещаться по всем правилам проходимости и занятости клетки. Если она занята или непроходима - юнит будет автоматически удален
	 * 		@ignore=false юнит будет помещаться в клетку в обход правил проходимости. Если клетка занята другим объектом - он будет удален.
	 */
	int Add(GameObject* newObject, int cell_x=-1, int cell_y=-1, bool ignore=false);

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

	Player* FindPlayer(int ID);

	void HandleMovement(int ID, int cell_x, int cell_y, bool replace=true);
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
	void WorkWithPlayer(EventForPlayer* EventInfo, int cell_x, int cell_y, Uint8* keystates);
	//передвижение карты :
	// изменяет облать карты которая отображается на экран
	// проверяя координаты мыши
	void MotionMap(Time t);
	void TakeOrder();
	//массив указателей на игроков
	std::vector<Player*> players;
	//указатель на игрока, которому будут переданы любые события
	Player* mainPlayer;

	void UnitHandler(int i, int k, Time t);
	void StructureHandler(int i, int k, Time t);
	void LootHandler(int i, int k, Time t);
	void EnvironmentHandler(int i, int k, Time t);

	bool UnitActionPossibility(int i, int k, Unit* unit);

	//методы касающиеся движения юнитов
	void WritePointQueueInUnit(Unit* unit,std::queue<Point> &controlPoints);
	void SendUnitTo(Unit* unit,int targetX, int targetY, std::vector<Point> &forbiddenPoints, bool replace=true);

	void ManageLoot(GameObject* object, Loot* loot);
};

#endif /* GAME_H_ */

/*
 * Unit.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef UNIT_H_
#define UNIT_H_

#include <cmath>
#include <queue>

#include "../Gameplay_Constants.h"
#include "../../../Constants.h"
#include "../../../Drawable/GameObjects/Action.h"
#include "../PlayingObject.h"
#include "../../../Rotating.h"

enum Units{ARCHER, SWORDMAN};

class Unit : public PlayingObject, public Rotating{
public:
	virtual ~Unit()=default;
	Unit(SDL_Rect src, const char *name_file_image,Units unitType, float maxSpeed=SPEED_DEFAULT,unsigned int maxHP=HP_UNIT_DEFAULT,int ownerID=0);
	void SetX(float x);
	void SetY(float y);

	/**
	 * Возвращают компоненты скоростей по координатам
	 */
	float GetXSpeed();
	float GetYSpeed();

	/**
	 * Фактически, возвращает sign(GetXSpeed()) и sign(GetYSpeed())
	 * Аналог старого sign из Game с расширенными возможностями
	 */
	int NextCellDirX();
	int NextCellDirY();

	/**
	 * @DirectMoveToCell добавлет в ActionQueue последовательность элементарных действий, чтобы добраться к цели
	 * Путь получается максимально короткий, без учета проходимости промежуточных ячеек
	 * @x_target - горизонтальные координаты целевой ячейки
	 * @y_target - вертикальные координаты целевой ячейки
	 * @replace - при значении true перед добавлением новой последовательности действий удаляет все текущие, прерывая их выполнение
	 */
	void DirectMoveToCell(int x_target,int y_target,bool replace=true);

	virtual void Stop();
	virtual void NextAction();

	virtual Units WhoIs();
private:
	const Units whoIs;
};

#endif /* UNIT_H_ */

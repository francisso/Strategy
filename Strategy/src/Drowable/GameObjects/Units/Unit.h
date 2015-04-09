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
#include "../PlayingObject.h"
#include "Action.h"

class Unit : public PlayingObject{
public:
	virtual ~Unit()=default;
	Unit(SDL_Rect src, const char *name_file_image,float maxSpeed=SPEED_DEFAULT,unsigned int maxHP=HP_DEFAULT,int ownerID=0);
	struct Action* GetAction() const;
	void StopUnitHard();
	// TODO нужны описания
	void AddAction(struct Action* action, bool replace=true);
	void NextAction();
	//float GetMaxSpeed() const;
	void SetX(CoordinateType x);
	void SetY(CoordinateType y);
	void SetDestinationX(float x);
	void SetDestinationY(float y);
	float GetDestinationX() const;
	float GetDestinationY() const;
	/**
	 * @DirectMoveToCell добавлет в ActionQueue последовательность элементарных действий, чтобы добраться к цели
	 * Путь получается максимально короткий, без учета проходимости промежуточных ячеек
	 * @x_target - горизонтальные координаты целевой ячейки
	 * @y_target - вертикальные координаты целевой ячейки
	 * @replace - при значении true перед добавлением новой последовательности действий удаляет все текущие, прерывая их выполнение
	 */
	void DirectMoveToCell(int x_target,int y_target,bool replace=true);
private:
	struct Action* action;
	std::queue<struct Action*> ActionQueue;
	//модуль скорости юнита
	//const float MaxSpeed;
protected:
	/**
	 * @DestinationX и @DestinationY хранят значения координат, в которых окажется юнит после выполнения всех действий ActionQueue
	 * При попытке добавить новые действия эти координаты обновятся.
	 * У стоячего юнита автоматически обновляются как положение юнита
	 */
	float DestinationX,DestinationY;
};

#endif /* UNIT_H_ */

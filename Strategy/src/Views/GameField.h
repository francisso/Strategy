/*
 * GameField.h
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#ifndef GAMEFIELD_H_
#define GAMEFIELD_H_

#include "../Constants.h"
#include "../GameObject.h"


//Содержит все игровые объекты
class GameField {
public:
	GameField();
	virtual ~GameField();
	//returns true if addition was successful
	bool AddGameObject(GameObject* addingObject, int type);
	GameObject* GetGameObjectAtCell(int x, int y);
	GameObject* GetGameObjectAtCoorinates(CoordinateType x, CoordinateType y);

private:

	enum CellType{ NOTHING, UNIT, BUILDING, WATER};
	struct Cell {
		CellType type;
		GameObject* object;};
	Cell* field[CELL_X_NUMBER][CELL_Y_NUMBER];

};

#endif /* GAMEFIELD_H_ */

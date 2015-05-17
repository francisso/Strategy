/*
 * GameField.cpp
 *
 *  Created on: May 3, 2015
 *      Author: staslatgttt
 */

#include "GameField.h"

void GameField::findPath(Point &startPoint, Point &finishPoint, std::queue<Point> &controlPoints)
{
	if(controlPoints.size()==0 && startPoint.x>0 && finishPoint.y>0) return;
	return;
}

bool GameField::IsWalkable(int x, int y){
	switch(this->grid[x][y].textureType){
	case WATER:
		return false;
	case SAND: case GROUND: case SWAMP:
		switch(this->grid[x][y].usedFor){
		case NOTHING:
			return true;
		case CellType::OBJECT_PART:
			return false;
		case OBJECT:
			switch(this->grid[x][y].object->GetObjectType()){
			case UNIT: case BUILDING: case ENVIRONMENT:
				return false;
			case LOOT:
				return true;
			}
			break;
		default:
			return false;
		}
		break;
	default:
		return false;
	}
	return false;
}

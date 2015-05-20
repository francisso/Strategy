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
	if(!this->IsInside(x,y))
		return false;
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

bool GameField::IsInside(int x, int y){
	if(((x<CELL_X_NUMBER) && (x>=0)) || ((y<CELL_Y_NUMBER) && (y>=0)))
		return true;
	else return false;
}

Point GameField::FindClosestFreeCell(int x, int y, int radius){
	radius=(radius>=0)?radius:maxRadiusDefault;
	Point point{-1,-1};
	int currDist, currMinDist=radius*2+1;
	for(int i=x-radius;i<x+radius+1;i++)
	for(int j=y-radius;j<y+radius+1;j++)
	{
		currDist=std::abs(i-x)+std::abs(j-y);
		if(IsWalkable(i,j) && (currDist<currMinDist)){
			point.x=i;
			point.y=j;
		}
	}
	return point;
}

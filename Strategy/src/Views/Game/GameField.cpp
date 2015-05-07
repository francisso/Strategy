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

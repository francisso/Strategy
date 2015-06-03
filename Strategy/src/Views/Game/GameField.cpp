/*
 * GameField.cpp
 *
 *  Created on: May 3, 2015
 *      Author: staslatgttt
 */

#include "GameField.h"

#include <stdlib.h>
extern "C" {
	#include "JumpPointSearch/jps_grid.h"
	#include "JumpPointSearch/neighbors.h"
	#include "JumpPointSearch/path.h"
	#include "JumpPointSearch/heap.h"
}

extern "C" void GameField::FindPath_JPS(Point &startPoint, Point &finishPoint, std::queue<Point> &controlPoints, std::vector<Point> &forbiddenPoints)
{
	//std::cout<<"Size of point queue: "<<controlPoints.size()<<std::endl;
	std::cout<<"Start point: x="<<startPoint.x<<" y="<<startPoint.y<<std::endl;
	std::cout<<"Finish point: x="<<finishPoint.x<<" y="<<finishPoint.y<<std::endl;
	struct grid gd;
	gd.width=CELL_X_NUMBER;
	gd.height=CELL_Y_NUMBER;
	gd.nodes=(struct node**)malloc(gd.height*sizeof(struct node*));
	for(int i=0;i<gd.height;i++)
	{
		gd.nodes[i]=(struct node*)malloc(gd.width*sizeof(struct node));
		for(int j=0;j<gd.height;j++)
		{
			gd.nodes[i][j]=createNode(j,i,this->IsWalkable(j,i,true,true));
		}
	}
	Point point;
	for(unsigned int i=0;i<forbiddenPoints.size();i++)
	{
		point=forbiddenPoints[i];
		gd.nodes[point.y][point.x].walkable=false;
	}

	//===========================================================================================================================
	struct neighbor_xy_list* path_head=NULL,*path_pos=NULL;
	path_head=findPath(&gd,startPoint.x, startPoint.y, finishPoint.x, finishPoint.y);
	path_pos=path_head;

	//path_head=smooth_path(&gd, path_head);
	//path_pos=path_head;

	int count=0;
	Point p;
	while(path_head!=NULL && (path_head!=(path_pos=path_pos->left))){
		//std::cout<<"Step "<<count<<": x="<<path_pos->x<<" y="<<path_pos->y<<std::endl;
		if(count>0){
			p.x=path_pos->x;
			p.y=path_pos->y;
			controlPoints.push(p);
		}
		count++;
	}

	neighbor_xy_clean(path_head);
	//===========================================================================================================================

	for(int i=0;i<gd.height;i++){
		free(gd.nodes[i]);
	}
	free(gd.nodes);
	//std::cout<<"Size of point queue: "<<controlPoints.size()<<std::endl;
	return;
}

bool GameField::IsWalkable(int x, int y, bool walkable_loot, bool walkable_unit){
	Unit* unit;
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
			case BUILDING: case ENVIRONMENT:
				return false;
			case UNIT:
				if(walkable_unit)
					return true;
				else
				{
					unit=dynamic_cast<Unit*>(this->grid[x][y].object);
					if(unit->GetAction()->type==MOVE)
						return true;
					else
						return false;
				}
			case LOOT:
				if(walkable_loot)
					return true;
				else
					return false;
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
	radius=(radius>0)?radius:maxRadiusDefault;
	Point point{-1,-1};
	int currDist, currMinDist=radius*2+1;
	for(int i=x-radius;i<x+radius+1;i++)
	for(int j=y-radius;j<y+radius+1;j++)
	{
		currDist=std::abs(i-x)+std::abs(j-y);
		if(IsWalkable(i,j, false) && (currDist<currMinDist)){
			point.x=i;
			point.y=j;
			currMinDist=currDist;
		}
	}
	std::cout<<"Closest point is x="<<point.x<<" y="<<point.y<<std::endl;
	return point;
}

Point GameField::FindPosition(Point target, Point currPos, float radius, std::vector<Point> &forbidden){
	Point resPoint={currPos.x, currPos.y};
	float currDist=Distance(target.x-currPos.x, target.y-currPos.y);
	float min=currDist+radius;
	if(currDist<=radius) return currPos;
	int radius_i=static_cast<int>(radius/CELL_X_PIXELS)+1;
	for(int i=target.x-radius_i;i<target.x+radius_i+1;i++)
	for(int j=target.y-radius_i;j<target.y+radius_i+1;j++){
		//std::cout<<i<<" "<<j<<std::endl;
		if(!IsWalkable(i,j)) continue;
		bool doIt=true;
		for(unsigned int k=0;k<forbidden.size();k++){
			if(i==forbidden[k].x && j==forbidden[k].y){
				doIt=false;
				break;
			}
		}
		if(!doIt) continue;
		float iterDist=Distance(target.x-i,target.y-j);
		if(iterDist>radius) continue;
		float currPosDist=Distance(currPos.x-i, currPos.y-j);
		if(currPosDist<min){
			min=currPosDist;
			resPoint.x=i;
			resPoint.y=j;
		}
	}
	std::cout<<"resPoint.x="<<resPoint.x<<" resPoint.y="<<resPoint.y<<std::endl;
	return resPoint;
}

float GameField::Distance(float x, float y){
	return std::sqrt(x*x+y*y);
}

float GameField::Distance(int dx, int dy){
	return Distance(CELL_X_PIXELS*static_cast<float>(dx), CELL_Y_PIXELS*static_cast<float>(dy));
}

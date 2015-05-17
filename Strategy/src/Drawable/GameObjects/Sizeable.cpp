/*
 * Sizeable.cpp
 *
 *  Created on: May 17, 2015
 *      Author: staslatgttt
 */

#include "Sizeable.h"

Sizeable::Sizeable(unsigned int sizeX, unsigned int sizeY): SizeX(sizeX), SizeY(sizeY){}

unsigned int Sizeable::GetSizeX(){
	return this->SizeX;
}

unsigned int Sizeable::GetSizeY(){
	return this->SizeY;
}



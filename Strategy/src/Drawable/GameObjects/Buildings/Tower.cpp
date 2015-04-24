/*
 * Tower.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: staslatgttt
 */

#include "../Buildings/Tower.h"

Tower::Tower(SDL_Rect stc, const char* name_file_image, int ownerID): Building(stc,name_file_image,TOWER,SPEED_DEFAULT,HP_TOWER_DEFAULT,ownerID,X_TOWER_DEFAULT,Y_TOWER_DEFAULT){}



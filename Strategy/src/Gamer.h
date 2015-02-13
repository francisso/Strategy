/*
 * Gamer.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef GAMER_H_
#define GAMER_H_

#include "Player.h"

//Описывает игрока - человека
//Отвечает за обработку ввода
class Gamer: public Player {
public:
	Gamer();
	virtual ~Gamer();
};

#endif /* GAMER_H_ */

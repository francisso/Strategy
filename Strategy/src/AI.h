/*
 * AI.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef AI_H_
#define AI_H_

#include "Player.h"

//В будущем этот класс будет отвечать за
//Искусственный интелект противника
class AI: public Player {
public:
	AI();
	virtual ~AI();
};

#endif /* AI_H_ */

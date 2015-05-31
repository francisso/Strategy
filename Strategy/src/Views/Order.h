/*
 * Order.h
 *
 *  Created on: 07 мая 2015 г.
 *      Author: ivanmatveev
 */

#ifndef VIEWS_ORDER_H_
#define VIEWS_ORDER_H_

#include "../Types.h"
#include "../Drawable/GameObjects/Unit.h"
#include "../Drawable/GameObjects/Building.h"

struct AmountOfUnit{
	GameObjectType object_type;
	UnitType unit_type;
	unsigned int amount;
};

struct Order {
	ReceiverType receiver;
	OrderType order;
	void* data;
	std::vector<AmountOfUnit>& counters;
	Building** building;
};


#endif /* VIEWS_ORDER_H_ */

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

struct AmountOfUnit{
	GameObjectType object_type;
	UnitType unit_type;
	unsigned int amount;
};

struct Order {
	ReceiverType receiver;
	OrderType order;
	const void* data;
	std::vector<AmountOfUnit>& counters;
};


#endif /* VIEWS_ORDER_H_ */

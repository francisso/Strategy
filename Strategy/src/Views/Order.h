/*
 * Order.h
 *
 *  Created on: 07 мая 2015 г.
 *      Author: ivanmatveev
 */

#ifndef VIEWS_ORDER_H_
#define VIEWS_ORDER_H_

#include "../Types.h"
#include "../Drawable/GameObjects/Units/Unit.h"

struct Order {
	ReceiverType receiver;
	OrderType order;
	const void* data;
};

struct AmountOfUnit{
	UnitType unit_type;
	unsigned int amount;
};
#endif /* VIEWS_ORDER_H_ */

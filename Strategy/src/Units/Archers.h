/*
 * Archers.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef ARCHERS_H_
#define ARCHERS_H_

#include "Unit.h"

typedef int Bitmap;

class Archers: public Unit {
public:
	virtual ~Archers();
private:
	static Bitmap archerImage;
};

#endif /* ARCHERS_H_ */

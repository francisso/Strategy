/*
 * Drawable.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "Types.h"

//Базовый интерфейс для любого объекта,
//который может быть отрисован
class  Drawable {
public:
	Drawable();
	virtual ~Drawable();
	virtual Bitmap GetImage() = 0;
	virtual CoordinateType X() {return x;};
	virtual CoordinateType Y() {return y;};
	virtual CoordinateType GetWidth() = 0;
	virtual CoordinateType GetHeight() = 0;
private:
	CoordinateType x;
	CoordinateType y;
};

#endif /* DRAWABLE_H_ */

/*
 * Drawable.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

typedef int CoordinateType;
typedef int Bitmap;

class  Drawable {
public:
	Drawable();
	virtual ~Drawable();
	virtual Bitmap getImage() = 0;
	virtual CoordinateType getX() = 0;
	virtual CoordinateType getY() = 0;
private:
	CoordinateType x;
	CoordinateType y;
};

#endif /* DRAWABLE_H_ */

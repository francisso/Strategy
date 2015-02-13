/*
 * Drawable.h
 *
 *  Created on: 12.02.2015
 *      Author: anton
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

//Временные типы, переопределить по необходимости
typedef int CoordinateType;
typedef int Bitmap;

//Базовый интерфейс для любого объекта,
//который может быть отрисован
class  Drawable {
public:
	Drawable();
	virtual ~Drawable();
	virtual Bitmap getImage() = 0;
	virtual CoordinateType getX() = 0;
	virtual CoordinateType getY() = 0;
};

#endif /* DRAWABLE_H_ */

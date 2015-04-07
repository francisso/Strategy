/*
 * IStatusObject.h
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#ifndef VIEWS_ISTATUSOBJECT_H_
#define VIEWS_ISTATUSOBJECT_H_

#include <string>
#include <SDL/SDL.h>
#include <functional>

#include "../Drawable.h"
/**
 * Элементарная ячейка с содержимым,
 * отображаюйщаяся в строке состояния
 */
class IStatusObject {
public:
	virtual ~IStatusObject()=default;

	virtual SDL_Rect* GetSize()=0;
	/**
	 * Кэшируя, возвращает Drawable* с текстом
	 * @return картинку с текстом
	 */
	virtual Drawable* GetTextImage()=0;

	/**
	 * Картинка, отобращающаяся рядом с текстом.
	 * Должна кэшироваться.
	 * В себе хранит координаты относительно строки состояния
	 */
	virtual Drawable* GetImage()=0;

	virtual bool Contains(int x, int y)=0;
	virtual void SetClicked()=0;
	virtual void Draw(std::function<void (Drawable*, float X0, float Y0)> f,
				Sint16 xOffset, Sint16 yOffset) const = 0;
private:
	/**
	 * @return текст, который будет отображаться
	 */
	virtual std::string GetText()=0;
	/**
	 * Координаты прямоугольника относительно начала строки состояния
	 * @return прямоугольник, в который рисуется текст.
	 *
	 */
	virtual SDL_Rect* GetTextRect()=0;
};

#endif /* VIEWS_ISTATUSOBJECT_H_ */

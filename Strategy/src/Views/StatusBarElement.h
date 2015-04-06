/*
 * StatusBarElement.h
 *
 *  Created on: Apr 4, 2015
 *      Author: anton
 */

#ifndef VIEWS_STATUSBARELEMENT_H_
#define VIEWS_STATUSBARELEMENT_H_

#include "IStatusObject.h"

class StatusBarElement: public IStatusObject {
public:
	StatusBarElement(Drawable* image, Drawable* selection,
			std::string name, SDL_Rect size, int x_offset, int y_offset);
	virtual SDL_Rect* GetSize();
	virtual ~StatusBarElement();

	//unused
	virtual Drawable* GetTextImage();
	/**
	* Картинка, отобращающаяся рядом с текстом.
	* Должна кэшироваться.
	* В себе хранит координаты относительно строки состояния
	*/
	virtual Drawable* GetImage();
private:
	//Картинка с отображаемым изображением
	Drawable* image;
	//Картинка, если ихображение выбранно
	//рисуется поверх старой
	Drawable* selected;
	//Имя объекта
	//в данном случае это имя текстуры.
	std::string name;

	//размеры элемента
	SDL_Rect size;

	//unused
	virtual std::string GetText();
	virtual SDL_Rect* GetTextRect();
};

#endif /* VIEWS_STATUSBARELEMENT_H_ */

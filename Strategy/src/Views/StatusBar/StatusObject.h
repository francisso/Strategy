/*
 * StatusObject.h
 *
 *  Created on: 05 мая 2015 г.
 *      Author: ivanmatveev
 */

#ifndef VIEWS_STATUSBAR_STATUSOBJECT_H_
#define VIEWS_STATUSBAR_STATUSOBJECT_H_

#include "IStatusObject.h"
#include <string>

class StatusObject: public IStatusObject {
public:
	StatusObject(Drawable* Image, SDL_Rect Rect_text);
	virtual ~StatusObject();
	/**
	 * Кэшируя, возвращает Drawable* с текстом
	 * @return картинку с текстом
	 */
	virtual Drawable* GetTextImage();

	/**
	 * Картинка, отобращающаяся рядом с текстом.
	 * Должна кэшироваться.
	 * В себе хранит координаты относительно строки состояния
	 */
	virtual Drawable* GetImage();
	/**
	 * @return текст, который будет отображаться
	 */
	virtual std::string GetText();
	/*
	 * Установка текста
	 */
	void SetText(std::string str);
	void SetText(const char* str);

	// Установка размера шрифта
	void SetSizeText(int size);
	// Установка цвета
	void SetColorText(SDL_Color clr);
	void SetColorText(int red, int green, int blue);
	bool ContainsCoordinates(Uint16 x, Uint16 y);
private:
	/**
	 * Координаты прямоугольника относительно начала строки состояния
	 * @return прямоугольник, в который рисуется текст.
	 */
	virtual SDL_Rect* GetTextRect();
	void CreateTextImage();
	std::string text;
	Drawable* image;
	Drawable* text_image;
	SDL_Rect rect_text;
	// цвет текста
	SDL_Color color;
	// размер текста
	int size_text;
};

#endif /* VIEWS_STATUSBAR_STATUSOBJECT_H_ */

/*
 * StatusBar.h
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#ifndef VIEWS_STATUSBAR_H_
#define VIEWS_STATUSBAR_H_

#include <vector>

#include <SDL/SDL.h>

#include "IStatusObject.h"
#include "StatusBarElement.h"
#include "View.h"
#include "../Drawable.h"

class StatusBar: public View {
public:
	StatusBar(Sint16 x, Sint16 y, Uint16 width, Uint16 height);
	virtual ~StatusBar()=default;
	virtual void Draw(std::function<void (Drawable*, float X0, float Y0)> f) const;
	void AddStatusObject(IStatusObject* object);
	void ClearStatusObjects();
	virtual bool OnEvent(SDL_Event* event);
	int GetTextureNumber();
private:
	//Массив элементов, которые рисуются в строке состояния
	std::vector<IStatusObject*> elements;
	void DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const;
	StatusBarElement* selected;
};

#endif /* VIEWS_STATUSBAR_H_ */

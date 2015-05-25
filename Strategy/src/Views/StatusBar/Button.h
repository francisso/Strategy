/*
 * Button.h
 *
 *  Created on: 25 мая 2015 г.
 *      Author: ivanmatveev
 */

#ifndef VIEWS_STATUSBAR_BUTTON_H_
#define VIEWS_STATUSBAR_BUTTON_H_

#include "StatusObject.h"
#include <functional>

class Button :public StatusObject {
public:
	Button(Drawable* Image, SDL_Rect Rect_text, std::function<void (SDL_Event* event)> Make_action);
	virtual ~Button() = default;
	void OnEvent(SDL_Event* event);
private:
	std::function<void (SDL_Event* event)> make_action;
};

#endif /* VIEWS_STATUSBAR_BUTTON_H_ */

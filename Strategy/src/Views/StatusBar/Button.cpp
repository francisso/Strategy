/*
 * Button.cpp
 *
 *  Created on: 25 мая 2015 г.
 *      Author: ivanmatveev
 */

#include "Button.h"

Button::Button(Drawable* Image, SDL_Rect Rect_text, std::function<void (SDL_Event* event)> Make_action) :
				StatusObject(Image, Rect_text),
				make_action(Make_action)
{}

void Button::OnEvent(SDL_Event* event){
	make_action(event);
}

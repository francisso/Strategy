/*
 * StatusBar.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#include "StatusBar.h"

void StatusBar::AddStatusObject(IStatusObject* object) {
	elements.push_back(object);
}

void StatusBar::ClearStatusObjects() {
	elements.clear();
}

void StatusBar::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const{
	for(auto e : elements)
		DrawElement(e, f);
	View::Draw(f);
}

void StatusBar::DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const {
	f(element->GetImage(),0.0f,0.0f);
	f(element->GetTextImage(),0.0f,0.0f);
}

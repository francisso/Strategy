/*
 * StatusBar.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#include "StatusBar.h"

StatusBar::StatusBar(Sint16 x, Sint16 y, Uint16 width, Uint16 height) {
	size = {x,y,width,height};
}

void StatusBar::AddStatusObject(IStatusObject* object) {
	elements.push_back(object);
}

void StatusBar::ClearStatusObjects() {
	elements.clear();
}

void StatusBar::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const{
	if (f == nullptr)
		return;
	View::Draw(f);
	for(auto e : elements)
		DrawElement(e, f);
}

void StatusBar::DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const {
	auto xOffset = static_cast<float>(this->size.x+element->GetSize()->x);
	auto yOffset = static_cast<float>(this->size.y+element->GetSize()->y);
	f(element->GetImage(),xOffset,yOffset);
	f(element->GetTextImage(),xOffset,yOffset);
}

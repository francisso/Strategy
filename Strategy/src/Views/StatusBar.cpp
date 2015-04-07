/*
 * StatusBar.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#include "StatusBar.h"

StatusBar::StatusBar(Sint16 x, Sint16 y, Uint16 width, Uint16 height) {
	size = {x,y,width,height};
	selected = nullptr;
}

void StatusBar::AddStatusObject(IStatusObject* object) {
	elements.push_back(object);
}

void StatusBar::ClearStatusObjects() {
	elements.clear();
}

void StatusBar::OnEvent(SDL_Event* event) {
	if (event == nullptr)
		return;
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		auto x =event->button.x-size.x;
		auto y =event->button.y-size.y;
		for(auto e:elements)
			if (e->Contains(x,y)) {
				e->SetClicked();
				if (selected != nullptr)
					selected->SetClicked();
				selected=dynamic_cast<StatusBarElement*>(e);
			}

	}
}



void StatusBar::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const{
	if (f == nullptr)
		return;
	View::Draw(f);
	for(auto e : elements)
		e->Draw(f, size.x, size.y);
}

void StatusBar::DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const {
	auto xOffset = static_cast<float>(this->size.x+element->GetSize()->x);
	auto yOffset = static_cast<float>(this->size.y+element->GetSize()->y);
	f(element->GetImage(),xOffset,yOffset);
	f(element->GetTextImage(),xOffset,yOffset);
}

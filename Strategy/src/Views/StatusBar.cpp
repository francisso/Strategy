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

bool StatusBar::OnEvent(SDL_Event* event) {
	if (event == nullptr)
		return false;
	if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
		auto x =event->button.x-size.x;
		auto y =event->button.y-size.y;
		for(auto e:elements)
			if (e->Contains(x,y)) {
				e->SetClicked();
				if (selected != nullptr)
					selected->SetClicked();
				selected=dynamic_cast<StatusBarElement*>(e);
				return true;
			}

	}
	return false;
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

int StatusBar::GetTextureNumber() {
	//TODO: по хорошему, это соответствие надо загружать из файла в словарь.
	if (selected==nullptr)
		return 0;
	if (!selected->GetName().compare("water"))
		return WATER;
	if (!selected->GetName().compare("forest"))
		return FOREST;
	if (!selected->GetName().compare("ground"))
		return GROUND;
	if (!selected->GetName().compare("mountian"))
		return MOUNTIAN;
	if (!selected->GetName().compare("swamp"))
		return SWAMP;
	if (!selected->GetName().compare("sand"))
		return SAND;
	return 0;
}

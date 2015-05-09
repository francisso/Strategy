/*
 * StatusBar.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#include "StatusBar.h"

StatusBar::StatusBar(std::function<void (StatusBar* status_bar)> f) {
	TTF_Init();
	make_orders = f;
	background = nullptr;
}

void StatusBar::Update(Time t){
	make_orders(this);
	View::Update(t);
}

void StatusBar::SetBackground(Drawable* back) {
	background = back;
}

void StatusBar::AddStatusObject(IStatusObject* object) {
	elements.push_back(object);
}

void StatusBar::ClearStatusObjects() {
	while (!elements.empty())
		elements.pop_back();
}

void StatusBar::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const{
	f(background, 0.0f, 0.0f);
	for(auto e : elements)
		DrawElement(e, f);
	View::Draw(f);
}

void StatusBar::DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const {
	f(element->GetImage(), background->GetX(), background->GetY());
	f(element->GetTextImage(), background->GetX(), background->GetY());
}

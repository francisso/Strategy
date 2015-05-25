/*
 * StatusBar.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#include "StatusBar.h"

void StatusBar::OnEvent(SDL_Event* event){
	if (event->type == SDL_EventType::SDL_MOUSEBUTTONUP ||
				event->type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		for (auto v: elements){
			auto but = dynamic_cast<Button*>(v);
			if (but && but->ContainsCoordinates(static_cast<Uint16>(event->button.x - background->GetX()),
								static_cast<Uint16>(event->button.y - background->GetY())))
				but->OnEvent(event);
		}
	}
		//Если не мышь - информируем всех
	else
		for(auto v: elements) {
			auto but = dynamic_cast<Button*>(v);
			if (but)
				but->OnEvent(event);
		}
	View::OnEvent(event);
}
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
	for (auto v: elements)
		delete v;
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

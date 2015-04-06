/*
 * View.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "View.h"


void View::Update(Time t) {
	for(auto v: views)
		v->Update(t);
}

void View::Draw(std::function<void (Drawable*, float X0, float Y0)> f) const {
	auto x = static_cast<float>(size.x);
	auto y = static_cast<float>(size.y);
	//Сначала рисуем фон
	if (image != nullptr)
		f(image, x, y);
	//Потом все drawables
	for(auto d : drawables)
		f(d, x, y);
	//Потом все view
	for(auto v: views)
		v->Draw(f);
}

void View::OnEvent(SDL_Event* event) {
	//Если произошло нажатие мышки, то отправляем только одному view
	if (event->type == SDL_EventType::SDL_MOUSEBUTTONUP ||
			event->type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		for(auto v: views)
			if (v->ContainsCoordinates(event->button.x, event->button.y))
				v->OnEvent(event);
	}
	//Если не мышь - информируем всех
	else
		for(auto v: views)
			v->OnEvent(event);
}

bool View::ContainsCoordinates(Uint16 x, Uint16 y) const {
	return image->ContainsCoordinates(x, y);
}

void View::AddDrawable(Drawable* drawable) {
	drawables.push_back(drawable);
}

void View::AddView(View* view) {
	views.push_back(view);
}

void View::SetImage(Drawable* image) {
	this->image = image;
}


/*
 * StatusBarElement.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: anton
 */

#include "StatusBarElement.h"

StatusBarElement::StatusBarElement(Drawable* image, Drawable* selected,
		std::string name, SDL_Rect size, int x_offset, int y_offset) {
	this->image = image;
	this->selected = selected;
	this->name = std::string(name);
	this->size=size;
	image->SetX(static_cast<float>(x_offset));
	image->SetY(static_cast<float>(y_offset));
	selected->SetX(static_cast<float>(x_offset));
	selected->SetY(static_cast<float>(y_offset));

}

StatusBarElement::~StatusBarElement() {
	// TODO Auto-generated destructor stub
}

SDL_Rect* StatusBarElement::GetSize() {
	return &size;
}

Drawable* StatusBarElement::GetTextImage() {
	return nullptr;
}
std::string StatusBarElement::GetText() {
	return nullptr;
}

SDL_Rect* StatusBarElement::GetTextRect() {
	return nullptr;
}

Drawable* StatusBarElement::GetImage() {
	return (clicked) ? selected : image;
}

void StatusBarElement::SetClicked() {
	clicked = !clicked;
}

bool StatusBarElement::Contains(int x, int y) {
	return (x > size.x && y > size.y &&
			x < size.x + size.w && y < size.y + size.h);
}


void StatusBarElement::Draw(std::function<void (Drawable*, float X0, float Y0)> f,
				Sint16 xOffset, Sint16 yOffset) const {
	xOffset =static_cast<Sint16>( size.x + xOffset);
	yOffset =static_cast<Sint16>(size.y+yOffset);
	f(image,xOffset, yOffset);
	if (clicked)
		f(selected,xOffset, yOffset);

}

std::string StatusBarElement::GetName() {
	return name;
}

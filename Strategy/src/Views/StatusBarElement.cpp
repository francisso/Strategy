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
	return image;
}


/*
 * View.cpp
 *
 *  Created on: 14 февр. 2015 г.
 *      Author: anton
 */

#include "View.h"

View::View() {
	// TODO Auto-generated constructor stub

}

View::~View() {
	// TODO Auto-generated destructor stub
}


void View::Draw(std::function<void (Drawable*)> f) {
	f(image);
	for(auto d : drawables)
		f(d);
	for(auto v: views)
		v->Draw(f);
}

void View::onEvent(SDL_Event event) {
	// TODO implement function
}

void View::Update(Time t) {
	//TODO implement function
}

/*
 * StatusObject.cpp
 *
 *  Created on: 05 мая 2015 г.
 *      Author: ivanmatveev
 */

#include "StatusObject.h"
#include "../../Drawable/Draw.h"

StatusObject::StatusObject(Drawable* Image, SDL_Rect Rect_text) {
	image = Image;
	SDL_Rect src = {0, 0, 200, 200};
	text_image = new Draw(src, "res/images/for_text.bmp");
	rect_text = Rect_text;
	text_image->SetDestRect(&Rect_text);
	color.b = 255;
	color.g = 255;
	color.r = 255;
	color.unused = 255;
	size_text = 20;
}

StatusObject::~StatusObject() {
	delete image;
	CreateTextImage();
}
void StatusObject::SetText(std::string str) {
	text = str;
	CreateTextImage();
}
void StatusObject::SetText(const char* str) {
	text = str;
	CreateTextImage();
}
Drawable* StatusObject::GetTextImage() {
	return text_image;
}

Drawable* StatusObject::GetImage() {
	return image;
}

std::string StatusObject::GetText() {
	return text;
}

SDL_Rect* StatusObject::GetTextRect() {
	return &rect_text;
}
void StatusObject::CreateTextImage(){
	// Загружаем шрифт по заданному адресу размером sz
	TTF_Font * fnt = TTF_OpenFont("res/font/courier.ttf", size_text);
	// Переносим на поверхность текст с заданным шрифтом и цветом
	text_image->SetImage( TTF_RenderText_Blended(fnt, text.c_str(), color));
	TTF_CloseFont(fnt); // Закрываем шрифт
}
void StatusObject::SetSizeText(int size){
	size_text = size;
}

void StatusObject::SetColorText(SDL_Color clr){
	color = clr;
}
void StatusObject::SetColorText(int red, int green, int blue){
	color.r = static_cast<Uint8>(red);
	color.g = static_cast<Uint8>(green);
	color.b = static_cast<Uint8>(blue);
	CreateTextImage();
}



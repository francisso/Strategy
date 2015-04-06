/*
 * ViewCreator.cpp
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#include "ViewCreator.h"

#include <fstream>

StatusBar* ViewCreator::CreateStatusBar(const char* path) {
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile (path);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("StatusBar");
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml %s\n", path);
	//определяем размеры строки состояния
	auto width = static_cast<Uint16>(atoi(root_node->first_attribute("width")->value()));
	auto height = static_cast<Uint16>(atoi(root_node->first_attribute("height")->value()));
	auto x = static_cast<Sint16>(atoi(root_node->first_attribute("x")->value()));
	auto y = static_cast<Sint16>(atoi(root_node->first_attribute("y")->value()));
	auto bar = new StatusBar(x,y,width,height);
	auto r = static_cast<Uint8>(atoi(root_node->first_attribute("r")->value()));
	auto g = static_cast<Uint8>(atoi(root_node->first_attribute("g")->value()));
	auto b = static_cast<Uint8>(atoi(root_node->first_attribute("b")->value()));
	//Устанавливаем фон
	auto back = new GameObject({0,0,width,height}, r,g,b);
	bar->SetImage(back);
	//добавляем подэлементы
	for (xml_node<> * element_node = root_node->first_node("StatusBarObject");
				element_node; element_node = element_node->next_sibling("StatusBarObject")) {
		bar->AddStatusObject(MakeElement(element_node));
	}
	printf("StatusBar is created\n");
	return bar;
}

StatusBarElement* ViewCreator::MakeElement(xml_node<>* node) {
	printf("Making a status bar element\n");
	auto name = node->first_attribute("name")->value();
	auto width = atoi(node->first_node("width")->value());
	auto height = atoi(node->first_node("height")->value());
	auto x = atoi(node->first_node("x")->value());
	auto y = atoi(node->first_node("y")->value());
	auto x_offset = atoi(node->first_node("pictureXOffset")->value());
	auto y_offset = atoi(node->first_node("pictureYOffset")->value());

	xml_node<> * drawable_node = node->first_node("Drawable");
    Drawable* picture = MakeDrawable(drawable_node);
    drawable_node = drawable_node->next_sibling("Drawable");
    Drawable* selection = MakeDrawable(drawable_node);
    SDL_Rect rect ={static_cast<Sint16>(x),static_cast<Sint16>(y),
    		static_cast<Uint16>(width), static_cast<Uint16>(height)};
    return new StatusBarElement(picture, selection, name, rect, x_offset, y_offset);
}

Drawable* ViewCreator::MakeDrawable(xml_node<>* node) {
	printf("Making a drawable\n");
	auto path = node->first_attribute("path")->value();
	auto width = atoi(node->first_attribute("width")->value());
	auto height = atoi(node->first_attribute("height")->value());
	auto x = atoi(node->first_attribute("x")->value());
	auto y = atoi(node->first_attribute("y")->value());
    printf("Read Drawable with path %s height %d width %d\n",
    	path,
    	width,
		height);
    SDL_Rect rect ={static_cast<Sint16>(x),static_cast<Sint16>(y),
    		static_cast<Uint16>(width), static_cast<Uint16>(height)};
    return new GameObject(rect, path);
}

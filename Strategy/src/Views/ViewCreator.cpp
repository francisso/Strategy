/*
 * ViewCreator.cpp
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#include "ViewCreator.h"

#include <fstream>

View* ViewCreator::CreateView(const char* path) {
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream theFile (path);
	std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("View");
	if (root_node == nullptr) {
		throw("Cannot find root node in xml");
	}
	printf("Started parsing xml %s\n", path);
	return MakeView(root_node);
}

View* ViewCreator::MakeView(xml_node<>* root_node) {
	printf("Making a view\n");
	View* view = new View();
	for (xml_node<> * drawable_node = root_node->first_node("Drawable");
				drawable_node; drawable_node = drawable_node->next_sibling("Drawable")) {
		view->AddDrawable(MakeDrawable(drawable_node));
	}
	for (xml_node<> * view_node = root_node->first_node("View");
					view_node; view_node = view_node->next_sibling()) {
		view->AddView(MakeView(view_node));
	}
	printf("View is created\n");
	return view;
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


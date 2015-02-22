/*
 * ViewCreator.h
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#ifndef VIEWS_VIEWCREATOR_H_
#define VIEWS_VIEWCREATOR_H_

#include "../../lib/rapidxml-1.13/rapidxml.hpp"

#include "View.h"

using namespace rapidxml;
//Создает объект View, считывая из
// xml файла
class ViewCreator {
public:
	//path - путь, по которому лежит xml для парсинга
	static View* CreateView(const char* path);

private:
	static View* MakeView(xml_node<>* root_node);
	static Drawable* MakeDrawable(xml_node<>* node);
	ViewCreator();
	virtual ~ViewCreator();
};

#endif /* VIEWS_VIEWCREATOR_H_ */

/*
 * ViewCreator.h
 *
 *  Created on: 18 февр. 2015 г.
 *      Author: anton
 */

#ifndef VIEWS_VIEWCREATOR_H_
#define VIEWS_VIEWCREATOR_H_

#include "../lib/rapidxml-1.13/rapidxml.hpp"

//Создает объект View, считывая из
// xml файла
class ViewCreator {
public:
	ViewCreator();
	virtual ~ViewCreator();
};

#endif /* VIEWS_VIEWCREATOR_H_ */

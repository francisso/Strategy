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
#include "../Engine/Engine.h"
#include "View.h"
#include "Game/Game.h"
#include "Game/GameField.h"
#include "StatusBar/StatusBar.h"
#include "Game/FieldBuilder.h"
#include "../Constants.h"
#include "../Drawable/GameObjects/Action.h"
#include "../Drawable/GameObjects/Units/Archer.h"
#include "../Drawable/GameObjects/Buildings/Tower.h"
#include "../Players/HumanPlayer.h"
#include "StatusBar/StatusObject.h"

using namespace rapidxml;
//Создает объект View, считывая из
// xml файла
class ViewCreator {
public:
	//path - путь, по которому лежит xml для парсинга
	static View* CreateView(const char* path);
	static View* CreateMainView(Engine* engine);

private:
	static View* MakeView(xml_node<>* root_node);
	static Drawable* MakeDrawable(xml_node<>* node);
	ViewCreator();
	virtual ~ViewCreator();
};

#endif /* VIEWS_VIEWCREATOR_H_ */

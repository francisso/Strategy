/*
 * StatusBar.h
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#ifndef VIEWS_STATUSBAR_H_
#define VIEWS_STATUSBAR_H_

#include <vector>

#include "IStatusObject.h"
#include "View.h"

class StatusBar: public View {
public:
	StatusBar()=default;
	virtual ~StatusBar()=default;
	virtual void Draw(std::function<void (Drawable*, float X0, float Y0)> f) const;
	void AddStatusObject(IStatusObject* object);
	void ClearStatusObjects();
private:
	//Массив элементов, которые рисуются в строке состояния
	std::vector<IStatusObject*> elements;
	void DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const;
};

#endif /* VIEWS_STATUSBAR_H_ */

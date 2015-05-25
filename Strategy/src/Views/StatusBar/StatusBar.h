/*
 * StatusBar.h
 *
 *  Created on: Apr 2, 2015
 *      Author: anton
 */

#ifndef VIEWS_STATUSBAR_H_
#define VIEWS_STATUSBAR_H_

#include <vector>
#include <list>
#include "IStatusObject.h"
#include "Button.h"
#include "../View.h"
#include "../Order.h"

// Размеры окна
extern float X_SIZE_WINDOW;
extern float Y_SIZE_WINDOW;
extern std::list<Order> list_of_orders;

class StatusBar: public View {
public:
	StatusBar(std::function<void (StatusBar* status_bar)> make_orders);
	virtual ~StatusBar()=default;
	void SetBackground(Drawable* back);
	virtual void Draw(std::function<void (Drawable*, float X0, float Y0)> f) const;
	void AddStatusObject(IStatusObject* object);
	void ClearStatusObjects();
	virtual void Update(Time t);
	virtual void OnEvent(SDL_Event* event);
private:
	//Массив элементов, которые рисуются в строке состояния
	std::vector<IStatusObject*> elements;
	Drawable* background;
	std::function<void (StatusBar* status_bar)> make_orders;
	void DrawElement(IStatusObject* element, std::function<void (Drawable*, float X0, float Y0)> f) const;
};

#endif /* VIEWS_STATUSBAR_H_ */

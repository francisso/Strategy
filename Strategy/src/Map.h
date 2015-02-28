/*
 * Map.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: anton
 */

#ifndef MAP_H_
#define MAP_H_


#include <functional>
#include "Constants.h"
#include "Drawable.h"

class Map {
public:
	Map(std::function<void (Drawable*)> f, SDL_Surface *screen);
	virtual ~Map();
	void Draw(std::function<void (Drawable*)> f);
	static Drawable* textures[6];
	SDL_Surface * background;

};

#endif /* MAP_H_ */

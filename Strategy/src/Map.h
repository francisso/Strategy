/*
 * Map.h
 *
 *  Created on: 26 февр. 2015 г.
 *      Author: anton
 */

#ifndef MAP_H_
#define MAP_H_


#include <functional>

#include "Drawable.h"

class Map {
public:
	Map();
	virtual ~Map();
	void Draw(std::function<void (Drawable*)> f);
	enum TextureTypes { GROUND, WATER, SAND, FOREST, MOUNTIAN, SWAMP};
	static Drawable* textures[6];

};

#endif /* MAP_H_ */

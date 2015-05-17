/*
 * Sizeable.h
 *
 *  Created on: May 17, 2015
 *      Author: staslatgttt
 */

#ifndef DRAWABLE_GAMEOBJECTS_SIZEABLE_H_
#define DRAWABLE_GAMEOBJECTS_SIZEABLE_H_

class Sizeable{
private:
	const unsigned int SizeX, SizeY;
public:
	Sizeable(unsigned int sizeX, unsigned int sizeY);
	~Sizeable()=default;
	unsigned int GetSizeX();
	unsigned int GetSizeY();
};



#endif /* DRAWABLE_GAMEOBJECTS_SIZEABLE_H_ */

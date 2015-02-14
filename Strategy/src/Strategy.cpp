//============================================================================
// Name        : Strategy.cpp
// Author      : Author
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <exception>
#include <iostream>

#include "Engine.h"
#include "Game.h"

int main() {
	std::cout << "I'm working fine";
	try
	{
		Game* game = new Game();
		game->Start();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
	return 0;
}

#include <iostream>

#include "GameDirector.h"
#include "BattleDisplay.h"

int main(int argc, char** argv)
{
	//Needed for random functions.
	srand(time(0));

	//Preparing display...
	Displayer displayer;

	GameDirector director(10, displayer);
	//Main simulation loop...
	director.Simulate();

	std::cout << "Program end!";
}
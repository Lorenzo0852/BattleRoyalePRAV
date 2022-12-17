#include <iostream>

#include "GameDirector.h"
#include "Displayer.h"

int main(int argc, char** argv)
{
	//Needed for random functions.
	srand(time(0));

	//Preparing display...
	Displayer displayer;

	GameDirector director(8, displayer);
	//Main simulation loop...
	director.Simulate();

	std::cout << "Program end!";
}
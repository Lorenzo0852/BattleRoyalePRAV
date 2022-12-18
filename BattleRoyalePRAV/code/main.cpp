#include <iostream>

#include "GameDirector.h"
#include "Displayer.h"

int main(int argc, char** argv)
{
	//Needed for random functions.
	srand(time(0));

	while (true)
	{
		//Preparing display...
		Displayer displayer;

		//Number of players need to be a power of 2
		GameDirector director(8, displayer);
		//Main simulation loop...
		director.Simulate();
		
		std::cout << "\n\n" << "Press [ENTER] to repeat or close this window to end the program." << "\n\n";
		std::cin.ignore();
	}
}
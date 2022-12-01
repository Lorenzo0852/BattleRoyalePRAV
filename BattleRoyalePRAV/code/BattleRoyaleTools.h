#pragma once

#include <random>

#include <iostream>
#include <ctime>


#ifdef PLATFORM_WINDOWS
	#define CLEAR_CONSOLE std::system("CLS")
#endif

#ifdef PLATFORM_LINUX | PLATFORM_MACOS
	#define CLEAR_CONSOLE std::system("clear")
#endif
	

namespace BRTools
{
	//Defining a database of names...
	static std::string names[15] =
	{
		"Pepe",
		"Jaime",
		"Mortadelo",
		"Confucio",
		"Alberto",
		"Nuria",
		"Irma",
		"Jesucristo",
		"Bejo",
		"Loco",
		"Willyrex",
		"Aristoteles",
		"Napoleon",
		"Filemon",
		"Verdun",
	};

	static inline int RandomRange(int from, int to)
	{
		return rand() % to + from;
	}

	static std::string RandomName()
	{
		return names[RandomRange(0,14)];
	}
}
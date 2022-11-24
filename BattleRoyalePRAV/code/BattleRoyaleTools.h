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
	static inline int RandomRange(int from, int to)
	{
		return rand() % to + from;
	}
}
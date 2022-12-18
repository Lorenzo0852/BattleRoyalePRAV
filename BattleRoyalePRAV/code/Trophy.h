#pragma once

/// <summary>
/// A dummy class so the winner can have an award.
/// </summary>
class Trophy
{
private:
	int shinyness = 0;
	int weight = 0;

public:
	Trophy(int shinyness, int weight) : shinyness(shinyness), weight(weight) {}
};


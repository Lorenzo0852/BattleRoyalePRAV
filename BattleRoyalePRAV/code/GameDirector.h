#pragma once

#include "Player.h"
#include "BattleDisplay.h"
#include "BattleRoyaleTools.h"

class GameDirector
{
	//A tick is a complete game loop
	//A round happens when all players have gone through a tick (so in 1vs1, 2 ticks, one per player).

	bool m_IsSimulating;

	int m_CurrentRound, m_CurrentTick;
	std::vector<Player* > m_Players;

public:

	/// <summary>
	/// Controls the flow of the simulation.
	/// </summary>
	/// <param name="amount_of_players">Amount of players to simulate. Needs to be even or it will get corrected.</param>
	/// <param name="display">Display controller to send information to</param>
	GameDirector(unsigned amount_of_players, Displayer & display);
	~GameDirector();

	void Simulate();

	void ChoosePairs();
	void NextRound();
	void NextTick();

	void Stop();
};
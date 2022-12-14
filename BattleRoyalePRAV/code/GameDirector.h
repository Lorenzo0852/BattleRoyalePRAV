#pragma once

#include "Player.h"
#include "Displayer.h"
#include "BattleRoyaleTools.h"
#include <queue>
#include <utility>
#include <map>

typedef std::vector<std::pair<Player*, Player*>>	BattleBuffer;

class GameDirector
{
private:
	std::vector<int> rng;

private:
	//A tick is a complete game loop
	//A round happens when all players have gone through a tick (so in 1vs1, 2 ticks, one per player).

	float m_DeltaTime = 750; //Set in ms

	bool m_IsSimulating = false;
	int m_CurrentRound = 1;
	int m_CurrentTick = 1;

	std::vector<Player* >	m_Players;
	BattleBuffer			m_BattleBuffer;

	//The displayer that's rendering everything to the console.
	Displayer& m_Displayer;

private:
	// Attacks per tick
	bool SimulateBattleTick();

public:

	/// <summary>
	/// Controls the flow of the simulation.
	/// </summary>
	/// <param name="amount_of_players">Amount of players to simulate. Needs to be a power of 2 or it will get corrected to the nearest provided.</param>
	/// <param name="display">Display controller to send information to</param>
	GameDirector(unsigned amount_of_players, Displayer & display);
	~GameDirector();

	void Simulate();
	void ChoosePairs();
	void ResetPlayersHP();

	void Stop();
};
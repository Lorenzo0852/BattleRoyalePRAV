#include "GameDirector.h"

GameDirector::GameDirector(unsigned amount_of_players, Displayer & displayer)
{
	//Force amount of players to be even
	if (amount_of_players % 2 != 0) --amount_of_players;

	m_Players.reserve(sizeof(Player*) * amount_of_players);


	displayer.Render(Displayer::Stage::PlayerSelection);

	Player * p = displayer.GetPlayerSelection();
	m_Players.push_back(p);
	displayer.AddPlayer(p);

	//i = 1 because player ID:0 is player-selected.
	for (int i = 1; i < amount_of_players; ++i)
	{
		Player* p = nullptr;
		int random = BRTools::RandomRange(0, 100);

		//Even chance to spawn different kinds of players.

		if (random < 33)
		{
			p = new Bruiser(i);
		}
		else if (random > 66)
		{
			p = new Healer(i);
		}
		else
		{
			p = new Tank(i);
		}

		m_Players.push_back(p);

		displayer.AddPlayer(p);
	}
	displayer.Render(Displayer::Stage::AddingPlayers);
}

void GameDirector::Simulate()
{
	m_IsSimulating = true;

	while (m_IsSimulating)
	{
		//
		//Choose pairs
		//Attack ticks
		//If half dead -> Choose pairs
		// 
		//If all dead -> Stop simulation
	}

	//Show winner name & config
	//cin -> Stop simulation
}

GameDirector::~GameDirector()
{
	for (Player * p : m_Players)
	{
		delete p;
	}

	m_Players.clear();
}
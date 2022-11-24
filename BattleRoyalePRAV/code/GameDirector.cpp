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
		ChoosePairs();
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

void GameDirector::ChoosePairs()
{
	int number_of_pairs = m_Players.size();
	
	Player* player1 = nullptr;
	Player* player2 = nullptr;

	std::vector<int> rng;
	rng.reserve(sizeof(int) * m_Players.size());

	for (int i = 0; i < m_Players.size(); ++i)
	{
		rng.push_back(i);
	}
	std::random_shuffle(rng.begin(), rng.end());

	for (int i = 0; i < rng.size(); i+=2)
	{
		player1 = m_Players[i];
		player2 = m_Players[i+1];

		m_BattleBuffer.push_back({player1, player2});
	}
}

GameDirector::~GameDirector()
{
	for (Player * p : m_Players)
	{
		delete p;
	}

	m_Players.clear();
}
#include "GameDirector.h"

GameDirector::GameDirector(unsigned amount_of_players, Displayer & displayer)
	:m_Displayer(displayer)
{
	//Force amount of players to be even
	if (amount_of_players % 2 != 0) --amount_of_players;

	m_Players.reserve(sizeof(Player*) * amount_of_players);


	m_Displayer.Render(Displayer::Stage::PlayerSelection);

	Player * p = displayer.GetPlayerSelection();
	m_Players.push_back(p);
	m_Displayer.AddPlayer(p);

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

		m_Displayer.AddPlayer(p);
	}
	m_Displayer.Render(Displayer::Stage::AddingPlayers);
}

void GameDirector::Simulate()
{
	m_IsSimulating = true;

	m_Displayer.Render(Displayer::Stage::Battle);

	bool generate_pairs = true;
	//Main simulation loop
	while (m_IsSimulating)
	{
		if (generate_pairs)
		{
			ChoosePairs();					//<----------------- Memleak
			generate_pairs = false;
		}				
		SimulateBattleTick();				//Attack ticks

		//If half dead -> Choose pairs, round++
		// 
		//If all dead -> Stop simulation


		//Meta stuff..
		++m_CurrentTick;
		Sleep(m_DeltaTime);
	}

	//Show winner name & config
	//cin -> Stop simulation
}

void GameDirector::SimulateBattleTick()
{
	//m_BattleBuffer
}

void GameDirector::ChoosePairs()
{
	std::vector<int> rng;																/**/// Leak is here
	rng.reserve(sizeof(int) * (m_Players.size() / m_CurrentRound) );			/**/// (fixed with sleep)

	for (int i = 0; i < m_Players.size(); ++i)
	{
		rng.push_back(i);
	}
	std::random_shuffle(rng.begin(), rng.end());

	for (int i = 0; i < rng.size(); i+=2)
	{
		m_BattleBuffer.push_back({ m_Players[i], m_Players[i + 1] });
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
#include "GameDirector.h"

//Number of players needs to be a power of 2. If not provided, it will default to the nearest power.
GameDirector::GameDirector(unsigned amount_of_players, Displayer & displayer)
	:m_Displayer(displayer)
{
	int corrected_players = amount_of_players;
	double log2 = std::log2(amount_of_players);

	//Checks if the number given is a power of 2.
	if ((int)log2 != log2)
	{
		//Force it to be a non-decimal power of 2
		corrected_players = std::pow(2,(int)log2);
	}

	m_Players.reserve(sizeof(Player*) * corrected_players);


	m_Displayer.Render(Displayer::Stage::PlayerSelection);

	Player * p = displayer.GetPlayerSelection();
	m_Players.push_back(p);
	m_Displayer.AddPlayerToPool(p);

	//i = 1 because player ID:0 is player-selected.
	for (int i = 1; i < corrected_players; ++i)
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

		m_Displayer.AddPlayerToPool(p);
	}
	m_Displayer.Render(Displayer::Stage::AddingPlayers);
}

void GameDirector::Simulate()
{
	m_IsSimulating = true;

	bool generate_pairs = true;

	int pairs = (m_Players.size() / 2) + 1;
	m_Displayer.InitializeBattleTable(pairs);

	//Main simulation loop
	while (m_IsSimulating)
	{
		if (m_Players.size() == 1)
		{
			//Only one player alive: it's the winner and stop the simulation.
			m_IsSimulating = false;
			break;
		}

		if (generate_pairs)
		{
			ChoosePairs();
			ResetPlayersHP();
			generate_pairs = false;
		}

		bool pairs_alive = SimulateBattleTick();				//Attack ticks

		if (!pairs_alive)
		{
			generate_pairs = true;
			++m_CurrentRound;
		}

		//Meta stuff..
		++m_CurrentTick;
		Sleep(m_DeltaTime);
	}

	Trophy trophy(BRTools::RandomRange(0,100), BRTools::RandomRange(0, 100));
	m_Players[0]->trophy = trophy;
	m_Displayer.SetWinner(m_Players[0], m_CurrentRound - 1);
	m_Displayer.Render(Displayer::Stage::PresentWinner);

	std::cout << "\n\n\n SIMULATION FINISHED \n";
}

void GameDirector::ResetPlayersHP()
{
	for (auto& p : m_Players)
	{
		p->ResetHP();
	}
}


bool GameDirector::SimulateBattleTick()
{
	std::queue<int> dead_ids;
	for (int i = 0; i < m_BattleBuffer.size(); ++i)
	{
		auto& first = m_BattleBuffer[i].first;
		auto& second = m_BattleBuffer[i].second;

		bool first_dead = !first->is_alive;
		bool second_dead = !second->is_alive;

		if (first_dead || second_dead)
		{
			if(first_dead)
				dead_ids.push(first->id);
			else
				dead_ids.push(second->id);

			continue;  //Skip battle simulation if one of them is dead.
		}

		if(m_CurrentTick % 2 != 0)
			first->Battle(*second);
		else
			second->Battle(*first);
	}

	if (dead_ids.size() == m_BattleBuffer.size()) //If the dead are == to totalplayers/2...
	{
		while (dead_ids.size() > 0)
		{
			for (int i = 0; i < m_Players.size(); ++i)
			{
				int dead_id = dead_ids.front();
				if (m_Players[i]->id == dead_id)
				{
					delete(m_Players[i]);
					m_Players.erase(m_Players.begin() + i);
					dead_ids.pop();
				}
			}
		}

		int debug = 0;
		m_BattleBuffer.clear();
		return false; //Has been completely simulated.
	}

	m_Displayer.Render(Displayer::Stage::Battle, &m_BattleBuffer);

	return true; //Simulation is ongoing.
}

void GameDirector::ChoosePairs()
{
	m_Displayer.ClearBattleTable();

	std::vector<int> rng;																/**/// Leak is here
	rng.reserve(sizeof(int) * (m_Players.size() / m_CurrentRound) );			/**/// ("fixed" with sleep)

	for (int i = 0; i < m_Players.size(); ++i)
	{
		rng.push_back(i);
	}
	std::random_shuffle(rng.begin(), rng.end());

	for (int i = 0; i < rng.size(); i+=2)
	{
		m_BattleBuffer.push_back({ m_Players[i], m_Players[i + 1] });
		m_Displayer.AddPairToBattle(m_Players[i], m_Players[i + 1]);
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
#pragma once

#include "BattleRoyaleTools.h"
#include "Player.h"
#include <tabulate/table.hpp>

using namespace tabulate;

class Displayer
{
public:
	enum Stage
	{
		PlayerSelection,
		AddingPlayers,
		Battle,
		PresentWinner
	};
private:
	//Selections...
	Table m_PlayerSelectionTable;
	Table m_AttackSelectionTable;
	//

	Table m_PlayerTable;
	Table m_BattleTable;
	Table m_WinnerTable;

	//Player selections...
	std::string player_name;
	Player::PlayerTypes m_PlayerTypeSelection;
	Attack::AttackType m_AttackTypeSelection[3];

	struct WinnerInfo
	{
		Player* winner;
		int roundsSurvived;
	};

	WinnerInfo m_WinnerInfo;

	Stage m_CurrentStage;

private:
	int m_BattleTicks = 1; //Increased each time a battle is rendered.
	int m_PlayersInBattle = 1; //Increased each time a player is added into battle.

private:
	//One time setups
	void SetupPlayerSelection();
	void SetupPlayerAddition();
	void SetupBattle();
	void SetupWinner();

	//Real-Time updates
	void RenderPlayerSelection();
	void RenderPlayerAddition();
	void RenderBattle(std::vector<std::pair < Player*, Player* > > * = nullptr);
	void RenderWinnerPresentation();

public:
	void AddPlayerToPool(Player* player);
	void InitializeBattleTable(int max_players);
	void AddPairToBattle(Player* player1, Player* player2);
	Player* GetPlayerSelection();

	inline void SetWinner(Player* winner, int roundsSurvived) { this->m_WinnerInfo.winner = winner; this->m_WinnerInfo.roundsSurvived = roundsSurvived; }
	void Render(Stage stage_to_render, std::vector<std::pair < Player*, Player* > > * battleBuffer = nullptr);
	void ClearBattleTable();

public:
	Displayer();
};
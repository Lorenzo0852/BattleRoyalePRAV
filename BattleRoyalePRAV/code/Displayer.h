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

	Stage m_CurrentStage;

private:
	//One time setups
	void SetupPlayerSelection();
	void SetupPlayerAddition();

	//Real-Time updates
	void RenderPlayerSelection();
	void RenderPlayerAddition();
	void RenderBattle();
	void RenderWinnerPresentation();

public:
	void AddPlayer(Player* player);
	Player* GetPlayerSelection();
	void Render(Stage stage_to_render);

public:
	Displayer();
};
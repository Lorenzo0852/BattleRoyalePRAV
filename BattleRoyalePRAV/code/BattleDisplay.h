#pragma once

#include "BattleRoyaleTools.h"
#include "Player.h"
#include <tabulate/table.hpp>

class Displayer
{

private:
	tabulate::Table m_PlayerTable;

	enum Stage
	{
		PlayerSelection,
		AddingPlayers,
		Battle,
		PresentWinner
	};

	Stage m_CurrentStage;

private:
	//One time setups
	void SetupPlayerAddition();

	//Real-Time updates
	void RenderPlayerAddition();

	void RenderBattle();
	void RenderWinnerPresentation();

public:
	void AddPlayer(Player* player);
	void Render();

public:
	Displayer();
};
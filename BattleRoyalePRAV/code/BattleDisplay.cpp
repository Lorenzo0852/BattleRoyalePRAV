#include "BattleDisplay.h"

using namespace tabulate;

Displayer::Displayer()
{
	SetupPlayerAddition();
}

void Displayer::AddPlayer(Player* player)
{
	Table& t = m_PlayerTable;

	int avg_dmg = (player->m_Attacks[0].damage + player->m_Attacks[1].damage + player->m_Attacks[2].damage) / 3;
	int avg_crit = (player->m_Attacks[0].critical_chance + player->m_Attacks[1].critical_chance + player->m_Attacks[2].critical_chance) / 3;

	t.add_row({ "[" + std::to_string(player->m_Id) + "] " + player->m_Name,			//NAME or ID
		(player->m_Attacks[0].GetName() + ", " +									//****
		player->m_Attacks[1].GetName() + ", " +										//Attacks
		player->m_Attacks[2].GetName()),											//****
		std::to_string(avg_dmg),													//AVG DMG
		std::to_string(avg_crit)});													//AVG CRIT		
}

void Displayer::Render()
{
	switch (m_CurrentStage)
	{
	case AddingPlayers:
		RenderPlayerAddition();
		break;
	case Battle:
		break;
	case PresentWinner:
		break;
	default:
		break;
	}
}

void Displayer::SetupPlayerAddition()
{
	m_CurrentStage = Stage::AddingPlayers;

	Table& t = m_PlayerTable;

	t.add_row({ "Player", "Abilities", "DAMAGE (avg)", "CRIT CHANCE (avg)" });

	t.format()
		.font_style({ FontStyle::bold })
		.border_top(" ")
		.border_bottom(" ")
		.border_left(" ")
		.border_right(" ")
		.corner(" ");

	t[0].format()
		.padding_top(1)
		.padding_bottom(1)
		.padding_left(10)
		.padding_right(10)
		.font_align(FontAlign::center)
		.font_style({ FontStyle::underline })
		.font_background_color(Color::red);

	t[0][2].format()
		.padding_top(1)
		.padding_bottom(1)
		.padding_left(5)
		.padding_right(5)
		.font_align(FontAlign::center)
		.font_style({ FontStyle::underline })
		.font_background_color(Color::cyan);

	t[0][3].format()
		.padding_top(1)
		.padding_bottom(1)
		.padding_left(5)
		.padding_right(5)
		.font_align(FontAlign::center)
		.font_style({ FontStyle::underline })
		.font_background_color(Color::green);

	t[0][1].format()
		.font_background_color(Color::blue)
		.font_color(Color::white);
}

void Displayer::RenderPlayerAddition()
{
	Table& t = m_PlayerTable;

	t.column(0).format()
		.font_color(Color::white)
		.font_align(FontAlign::center);

	t.column(1).format()
		.font_color(Color::yellow)
		.font_align(FontAlign::center);

	t.column(2).format()
		.font_color(Color::white)
		.font_align(FontAlign::center);

	t.column(3).format()
		.font_color(Color::yellow)
		.font_align(FontAlign::center);

	std::cout << t;
}
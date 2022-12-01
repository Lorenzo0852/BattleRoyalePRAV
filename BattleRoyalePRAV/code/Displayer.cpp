#include "Displayer.h"


Displayer::Displayer()
{
	SetupPlayerSelection();
	SetupPlayerAddition();
	SetupBattle();
}

void Displayer::AddPlayer(Player* player)
{
	Table& t = m_PlayerTable;

	int avg_dmg = (player->m_Attacks[0].damage + player->m_Attacks[1].damage + player->m_Attacks[2].damage) / 3;
	int avg_crit = (player->m_Attacks[0].critical_chance + player->m_Attacks[1].critical_chance + player->m_Attacks[2].critical_chance) / 3;

	//ID + ROLE + NAME + ATTACKS + AVD DMG + AVG CRIT

	t.add_row({ "[" + std::to_string(player->m_Id) + "] ",								//ID
		player->m_Role,																	//ROLE
		player->m_Name,																	//NAME
		(player->m_Attacks[0].GetName() + ", " +										//****
		player->m_Attacks[1].GetName() + ", " +											//Attacks
		player->m_Attacks[2].GetName()),												//****
		std::to_string(avg_dmg),													//AVG DMG
		std::to_string(avg_crit)});													//AVG CRIT		
}

void Displayer::Render(Stage stage_to_render)
{
	m_CurrentStage = stage_to_render;

	CLEAR_CONSOLE;

	switch (stage_to_render)
	{
	case PlayerSelection:
		RenderPlayerSelection();
		break;
	case AddingPlayers:
		RenderPlayerAddition();
		break;
	case Battle:
		RenderBattle();
		break;
	case PresentWinner:
		RenderWinnerPresentation();
		break;

	default:
		RenderPlayerSelection();
		break;
	}
}

//Setups only happen once per table.
void Displayer::SetupPlayerSelection()
{
	Table& t_player = m_PlayerSelectionTable;
	Table& t_attack = m_AttackSelectionTable;

	//Player table content...
	{
		t_player.add_row({ "ID",	"Roles",		"Description" });
		t_player.add_row({ "0",	"Bruiser",		"15% chance to deal 10 more damage" });
		t_player.add_row({ "1",	"Healer",		"55% chance to heal itself 5 HP" });
		t_player.add_row({ "2",	"Tank",			"15% damage reduction" });
	}

	//Player types customization
	{
		t_player.format()
			.font_align(FontAlign::center);

		t_player.format()
			.font_style({ FontStyle::bold })
			.border_top(" ")
			.border_bottom(" ")
			.border_left(" ")
			.border_right(" ")
			.corner(" ");

		t_player[0].format()
			.padding_top(1)
			.padding_bottom(1)
			.padding_left(3)
			.padding_right(3)
			.font_align(FontAlign::center)
			.font_style({ FontStyle::underline })
			.font_background_color(Color::red);

		t_player.column(0).format()
			.font_color(Color::yellow);

		t_player[0][1].format()
			.padding_top(1)
			.padding_bottom(1)
			.padding_left(10)
			.padding_right(10)
			.font_align(FontAlign::center)
			.font_style({ FontStyle::underline })
			.font_background_color(Color::magenta);
	}

	/***/ /***/ /***/ /***/ /***/ /***/

	//Attack table content...
	{
		t_attack.add_row({ "ID",	"Attacks", "Damage", "Critical Hit (%)" });
		t_attack.add_row({ "0",	"Melee",	"15",	"5 %" });
		t_attack.add_row({ "1",	"Shot",		"35",	"5 %" });
		t_attack.add_row({ "2",	"Charge",	"25",	"5 %" });
		t_attack.add_row({ "3",	"Cut",		"55",	"0 %" });
		t_attack.add_row({ "4",	"Punch",	"10",	"75 %" });
		t_attack.add_row({ "5",	"Headbutt",	"5",	"10 %" });
		t_attack.add_row({ "6",	"Execution", "70",	"1 %" });
	}
	//Attacks customization
	{
		t_attack.format()
			.font_align(FontAlign::center);

		t_attack.format()
			.font_style({ FontStyle::bold })
			.border_top(" ")
			.border_bottom(" ")
			.border_left(" ")
			.border_right(" ")
			.corner(" ");

		t_attack[0].format()
			.padding_top(1)
			.padding_bottom(1)
			.padding_left(3)
			.padding_right(3)
			.font_align(FontAlign::center)
			.font_style({ FontStyle::underline })
			.font_background_color(Color::blue);

		t_attack.column(0).format()
			.font_color(Color::yellow);

		t_attack[0][1].format()
			.padding_top(1)
			.padding_bottom(1)
			.padding_left(10)
			.padding_right(10)
			.font_align(FontAlign::center)
			.font_style({ FontStyle::underline })
			.font_background_color(Color::red);

		t_attack.column(2)[0].format()
			.padding_top(1)
			.padding_bottom(1)
			.padding_left(10)
			.padding_right(10)
			.font_align(FontAlign::center)
			.font_style({ FontStyle::underline })
			.font_background_color(Color::magenta);
	}
}
void Displayer::SetupPlayerAddition()
{
	m_CurrentStage = Stage::AddingPlayers;

	Table& t = m_PlayerTable;

	t.add_row({ "ID", "Role", "Name", "Abilities", "DAMAGE (avg)", "CRIT CHANCE (avg)" });

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

	t.column(0).format()
		.padding_left(2)
		.padding_right(2);


	t.column(1).format()
		.padding_left(3)
		.padding_right(3);

	t.column(4).format()
		.padding_left(1)
		.padding_right(1);

	t.column(5).format()
		.padding_left(1)
		.padding_right(1);
}
void Displayer::SetupBattle()
{
	Table& t = m_BattleTable;

	//ROLE / NAME / ATTACK / HP <-> (reflected)
	{
		t.add_row({ "ROLE",	"NAME",		"ATTACK", "HP", "HP", "ATTACK", "NAME", "ROLE"});
			

		t.format()
			.font_style({ FontStyle::bold })
			.border_top(" ")
			.border_bottom(" ")
			.border_left(" ")
			.border_right(" ")
			.corner(" ")
			.font_align(FontAlign::center);;

		t[0].format()
			.padding_top(1)
			.padding_bottom(1)
			.padding_left(3)
			.padding_right(3)
			.font_align(FontAlign::center)
			.font_style({ FontStyle::underline })
			.font_background_color(Color::red);

		t.column(0).format()
			.font_color(Color::yellow);
	}

}

//Renders happen everytime the Render() function is called.
void Displayer::RenderPlayerSelection()
{
	std::string player_name;
	int player_type;
	int player_attacks[3];

	Table& t_player = m_PlayerSelectionTable;

	std::cout << "Write your player name: ";
	std::cin >> player_name;
	
	this->player_name = player_name;

	CLEAR_CONSOLE;

	std::cout << t_player << "\n";

	std::cout << "\n Select your role ID: ";
	std::cin >> player_type;

	CLEAR_CONSOLE;
	Table& t_attack = m_AttackSelectionTable;


	std::cout << t_attack << "\n";

	std::cout << "\n You can choose three of any of these attacks. Choose wisely: \n \n";
	std::cout << "- Select your first attack ID:  ";
	std::cin >> player_attacks[0];
	std::cout << "- Select your second attack ID: ";
	std::cin >> player_attacks[1];
	std::cout << "- Select your third attack ID:  ";
	std::cin >> player_attacks[2];

	m_AttackTypeSelection[0] = (Attack::AttackType)player_attacks[0];
	m_AttackTypeSelection[1] = (Attack::AttackType)player_attacks[1];
	m_AttackTypeSelection[2] = (Attack::AttackType)player_attacks[2];
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

	std::cout << "\n\n" << "PRESS ENTER TO START THE BATTLE";
	std::cin.ignore();
	std::cin.ignore();
}
void Displayer::RenderBattle()
{
	Table& t = m_BattleTable;

	//t.add_row({ "ROLE",	"NAME",		"ATTACK", "HP", "HP", "ATTACK", "NAME", "ROLE" });




	std::cout << t;
}
void Displayer::RenderWinnerPresentation()
{
	Table& t = m_WinnerTable;
	std::cout << t;
}

//Returns a player pointer with all user selected options.
Player* Displayer::GetPlayerSelection()
{
	//Default ID is 0.

	Player* p = nullptr;

	switch (m_PlayerTypeSelection)
	{
	case Player::PlayerTypes::Bruiser:
		p = new Bruiser(0);
		p->m_Attacks[0] = (Attack::AttackType)m_AttackTypeSelection[0];
		p->m_Attacks[1] = (Attack::AttackType)m_AttackTypeSelection[1];
		p->m_Attacks[2] = (Attack::AttackType)m_AttackTypeSelection[2];
		p->m_Name = player_name;
		break;
	case Player::PlayerTypes::Tank:
		p = new Tank(0);
		p->m_Attacks[0] = (Attack::AttackType)m_AttackTypeSelection[0];
		p->m_Attacks[1] = (Attack::AttackType)m_AttackTypeSelection[1];
		p->m_Attacks[2] = (Attack::AttackType)m_AttackTypeSelection[2];
		p->m_Name = player_name;
		break;
	case Player::PlayerTypes::Healer:
		p = new Healer(0);
		p->m_Attacks[0] = (Attack::AttackType)m_AttackTypeSelection[0];
		p->m_Attacks[1] = (Attack::AttackType)m_AttackTypeSelection[1];
		p->m_Attacks[2] = (Attack::AttackType)m_AttackTypeSelection[2];
		p->m_Name = player_name;
		break;
	default:
		p = new Bruiser(0);
		p->m_Name = player_name;
	}

	return p;
}
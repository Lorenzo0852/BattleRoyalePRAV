#include "Player.h"

Player::Player(int id, int health)
	:
	m_Health(health),
	m_Id(id)
{
	for (int i = 0; i < 3; ++i)
	{
		int random_attack = BRTools::RandomRange(0, Attack::AttackType::Count);
		Attack attack((Attack::AttackType) random_attack);

		m_Attacks[i] = attack;
	}

	
}

void Player::Battle(Player& other)
{
	//stuff per tick
}

Bruiser::Bruiser(int id) :
	Player(id)
{
	m_Name = "Bruiser";
}

Healer::Healer(int id) :
	Player(id)
{
	m_Name = "Healer";
}

Tank::Tank(int id) :
	Player(id)
{
	m_Name = "Tank";
}

void Bruiser::Battle(Player& other)
{
	//stuff per tick
}

void Healer::Battle(Player& other)
{
	//stuff per tick
}

void Tank::Battle(Player& other)
{
	//stuff per tick
}
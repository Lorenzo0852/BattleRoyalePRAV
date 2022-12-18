#include "Player.h"
#include <assert.h>

Player::Player(int id, int health)
	:
	m_Health(health),
	id(id),
	role("Default"),
	name("Default_Name")
{
	for (int i = 0; i < 3; ++i)
	{
		int random_attack = BRTools::RandomRange(0, Attack::AttackType::Count);
		Attack attack((Attack::AttackType) random_attack);

		attacks[i] = attack;
	}
}

//stuff per tick
std::string Player::Battle(Player& other)
{
	int attack = BRTools::RandomRange(0, 3);
	int dmg = attacks[attack].DealDamage();

	other.ReceiveDamage(dmg);
	std::string attack_name = attacks[attack].GetName();
	m_LastUsedAttack = attack_name;
	return attack_name;
}

void Player::ReceiveDamage(int dmg)
{
	this->m_Health -= dmg;

	if (m_Health < 0)
	{
		m_Health = 0;
		is_alive = false;
	}
}

Bruiser::Bruiser(int id) :
	Player(id)
{
	role = "Bruiser";
	name = BRTools::RandomName();
}

std::string Bruiser::Battle(Player& other)
{
	int attack = BRTools::RandomRange(0, 3);
	int dmg = attacks[attack].DealDamage();

	//Bruiser has a 15% chance of dealing +10 dmg
	int chance = BRTools::RandomRange(0, 100);

	if (chance <= m_ActivationChance) dmg += m_AdditionalDamage;

	other.ReceiveDamage(dmg);

	std::string attack_name = attacks[attack].GetName();
	m_LastUsedAttack = attack_name;

	return attack_name;
}

Healer::Healer(int id) :
	Player(id)
{
	role = "Healer";
	name = BRTools::RandomName();
}

std::string Healer::Battle(Player& other)
{
	int chance = BRTools::RandomRange(0, 100);
	
	if (chance <= m_ActivationChance) m_Health += m_Healing; //Can overflow to +100 by design.
	
	return Player::Battle(other);
}

Tank::Tank(int id) :
	Player(id)
{
	role = "Tank";
	name = BRTools::RandomName();
}

std::string Tank::Battle(Player& other)
{
	return Player::Battle(other);
	//stuff per tick
}

void Tank::ReceiveDamage(int dmg)
{
	int new_dmg = dmg;

	int chance = BRTools::RandomRange(0, 100);
	if (chance <= m_ActivationChance)
	{
		float modifier = 1 - m_DamageReduction;
		new_dmg = dmg * (modifier * 0.01);
	}
	
	Player::ReceiveDamage(new_dmg);
}
#pragma once

#include <random>
#include <string>

#include "BattleRoyaleTools.h"


/*
*	Attacks behaviour...
*/

class Attack
{
public:
	enum AttackType
	{
		Melee = 0,
		Shot,
		Charge,
		Cut,
		Punch,
		Headbutt,
		Execution,
		Count
	};

private:
	AttackType type;
	std::string name;

public:
	int damage;
	int critical_chance;

	inline std::string GetName()
	{
		return name;
	}

	inline int DealDamage()
	{
		int critical_hit_modifier = 1;
		if (BRTools::RandomRange(0, 100) < critical_chance)
			critical_hit_modifier = 2;
		else
			critical_hit_modifier = 1;

		return damage * critical_hit_modifier;
	}

public:
	Attack() = default;
	Attack(AttackType attack_type);
	~Attack() = default;
};
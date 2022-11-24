#include "Attack.h"

Attack::Attack(AttackType attack_type)
{
	type = attack_type;

	switch (type)
	{

	case AttackType::Melee:
		damage = 15;
		critical_chance = 5;
		this->name = "Melee";
		break;
	case AttackType::Shot:
		damage = 35;
		critical_chance = 5;
		this->name = "Shot";
		break;
	case AttackType::Charge:
		damage = 25;
		critical_chance = 5;
		this->name = "Charge";
		break;
	case AttackType::Cut:
		damage = 55;
		critical_chance = 0;
		this->name = "Cut";
		break;
	case AttackType::Punch:
		damage = 10;
		critical_chance = 75;
		this->name = "Punch";
		break;
	case AttackType::Headbutt:
		damage = 5;
		critical_chance = 10;
		this->name = "Headbutt";
		break;
	case AttackType::Execution:
		damage = 70;
		critical_chance = 1;
		this->name = "Execution";
		break;
	default:
		damage = 1;
		critical_chance = 1;
		this->name = "Undefined";
	}
}
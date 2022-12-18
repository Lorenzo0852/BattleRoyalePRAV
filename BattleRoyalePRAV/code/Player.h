#pragma once

#include "Attack.h"
#include "Trophy.h"

class Player
{
public:
	enum PlayerTypes
	{
		Bruiser = 0,
		Healer,
		Tank,
		Count
	};

protected:
	//Base health
	int m_Health = 100;
	std::string m_LastUsedAttack = "";

public:
	int id;
	std::string role;
	std::string name;
	bool is_alive = true;

	Attack attacks[3];
	Trophy trophy;

public:
	Player(int id, int health = 100);
	virtual ~Player() {};

public:
	/// <summary>
	/// Battles another player.
	/// </summary>
	/// <param name="other">other player</param>
	/// <returns>Attack Type used</returns>
	virtual std::string Battle(Player& other);
	virtual void ReceiveDamage(int damage);

	inline void ResetHP() { m_Health = 100; }
	inline int GetHP() { return m_Health; }
	inline std::string GetLastAttack() { return m_LastUsedAttack; }
};

class Bruiser : public Player
{
private:
	int m_AdditionalDamage = 10;
	int m_ActivationChance = 15;
public:
	Bruiser(int id);
	~Bruiser() override {};

	virtual std::string Battle(Player& other) override;
};

class Healer : public Player
{
private:
	int m_Healing = 5;
	int m_ActivationChance = 55;
public:
	Healer(int id);
	~Healer() override {};

	virtual std::string Battle(Player& other) override;
};

class Tank : public Player
{
private:
	int m_DamageReduction = 15;
	int m_ActivationChance = 15;

public:
	Tank(int id);
	~Tank() override {};

	virtual std::string Battle(Player& other) override;
	virtual void ReceiveDamage(int dmg) override;
};
#pragma once

#include "Attack.h"

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

public:
	int m_Id;
	//Base health
	int m_Health = 100;
	std::string m_Role;
	std::string m_Name;

	Attack m_Attacks[3];

public:
	Player(int id, int health = 100);
	virtual ~Player() {};

public:
	virtual void Battle(Player& other);
};

class Bruiser : public Player
{
public:
	Bruiser(int id);
	~Bruiser() override {};

	virtual void Battle(Player& other) override;
};

class Healer : public Player
{
public:
	Healer(int id);
	~Healer() override {};

	virtual void Battle(Player& other) override;
};

class Tank : public Player
{
public:
	Tank(int id);
	~Tank() override {};

	virtual void Battle(Player& other) override;
};
#ifndef BATTLEPARAMS
#define BATTLEPARAMS

#include <memory>
#include <vector>
#include "..\Entities\Entity.hpp"
#include "..\Entities\Player.hpp"
#include <iostream>
#include <windows.h>

struct Params
{
	std::string State;
	std::unique_ptr<Player> Player;

	virtual void test() {}

	Params(const std::string& state) :State(state)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		std::cout << "params: " << State << " created" << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	~Params()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		std::cout << "params: " << State << " deleted" << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
};

struct BattleParams : public Params
{
	std::unique_ptr<std::vector<Entity*>> Enemies;

	virtual void test() {}

	BattleParams(const std::string& state, std::unique_ptr<std::vector<Entity*>> enemies) : Params(state), Enemies(std::move(enemies))
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		std::cout << "battleparams: created" << std::endl;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

};

#endif


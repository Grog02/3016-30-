#pragma once

#include "Header.h"

class Character
{


public:
	Character();

	std::string name = " ", race = " ", sex = " ";
	std::string invalidRace = "Human";
	std::vector<std::string> playerRace;
	int hp, /*totalHealth*/ maxHealth, heal, attack, defence;
	 
	int level, currentXp, baseXp, xpToLevel, minLevel, maxLevel;
	void CharacterCreation();
};


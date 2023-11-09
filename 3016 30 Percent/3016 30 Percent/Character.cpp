#include "Character.h"



Character::Character()
{
	name = " ";
	race = " ";
	sex = " ";

	playerRace = { "elf", "dwarf", "goblin", "wizard", "ogre" };
	invalidRace;
	level = 0, hp = 0, totalHealth = 0, maxHealth = 0, heal = 0, attack = 0, evasion = 0, defence = 7;

	level = 1, currentXp = 0, xpToLevel = 1, minLevel = 1, maxLevel = 10;


}

void Character::CharacterCreation()
{

	int counter = 0;

	//player information for character creation
	std::cout << "Enter Character's name: ";
	std::getline(std::cin, name);


	std::cout << "Enter Character's race\n";
	std::cout << "Elf\n";
	std::cout << "Viking\n";
	std::cout << "Goblin\n";
	std::cout << "Wizard\n";
	std::cout << "Ogre\n";
	std::cout << "Type your race below: \n\n";
	std::getline(std::cin, race);


	std::transform(race.begin(), race.end(), race.begin(), ::tolower); // Convert the input to lowercase

	bool validRace = false; // check if a valid race was found

	for (int i = 0; i < sizeof(playerRace); i++) {
		if (race == "elf") {
			hp = 40;
			attack = 5;
			defence = 3;
			evasion = 7;
			validRace = true;
			break;
		}
		else if (race == "viking") {
			hp = 70;
			attack = 7;
			defence = 5;
			evasion = 3;
			validRace = true;
			break;
		}
		else if (race == "goblin") {
			hp = 48;
			attack = 4;
			defence = 1;
			evasion = 8;
			validRace = true;
			break;
		}
		else if (race == "wizard") {
			hp = 40;
			attack = 9;
			defence = 2;
			evasion = 6;
			validRace = true;
			break;
		}
		else if (race == "ogre") {
			hp = 100;
			attack = 10;
			defence = 4;
			evasion = 0;
			validRace = true;
			break;
		}
		std::cout << "Invalid race choice. You will be a Human" << std::endl;
		race = invalidRace;
		hp = 25;
		attack = 3;
		defence = 3;
		evasion = 4;
		break;

	}


	std::cout << "\n";
	std::cout << "Enter Character's sex: ";
	std::getline(std::cin, sex);

	// Loading screen 
	system("cls");
	Sleep(200);
	for (int i = 0; i <= counter; i++)
	{

		if (i == 0)
		{
			std::cout << "Creating Character.\n";
			std::cout << "---->                   O\n";

		}
		if (i == 1)
		{
			std::cout << "Creating Character..\n";
			std::cout << "--------------->        O\n";
		}
		if (i == 2)
		{
			std::cout << "Creating Character...\n";
			std::cout << "----------------------->O\n";
			break;
		}
		Sleep(400);
		system("cls");
		counter++;
	}

	name[0] = toupper(name[0]);
	race[0] = toupper(race[0]);
	sex[0] = toupper(sex[0]);
	totalHealth = hp;
	maxHealth = totalHealth;
}
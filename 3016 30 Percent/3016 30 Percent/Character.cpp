#include "Character.h"



Character::Character()
{
	name = " ";
	race = " ";
	sex = " ";

	playerRace = { "elf", "viking", "goblin", "wizard", "ogre" };
	invalidRace;
	level = 0, hp = 0, /*totalHealth = 0,*/ maxHealth = 0, heal = 0, attack = 0, defence = 7;

	level = 1, currentXp = 0, xpToLevel = 10, minLevel = 1, maxLevel = 10;


}

void Character::CharacterCreation()
{

	int counter = 0;
	bool validRace = false; // check if a valid race was found
	std::string raceFromFile;
	int hpFromFile, attackFromFile, defenceFromFile;

	//player information for character creation
	std::cout << "Enter Character's name: ";
	std::getline(std::cin, name);


	std::cout << "Enter Character's class\n";
	std::cout << "Elf\n";
	std::cout << "Viking\n";
	std::cout << "Goblin\n";
	std::cout << "Wizard\n";
	std::cout << "Ogre\n";
	std::cout << "Type your class below: \n\n";
	std::getline(std::cin, race);


	std::transform(race.begin(), race.end(), race.begin(), ::tolower); // Convert the input to lowercase

	std::ifstream file("stats.txt");


	if (file.is_open()) {
		while (file >> raceFromFile >> hpFromFile >> attackFromFile >> defenceFromFile) 
		{
			// Convert the race input to lowercase
			std::transform(race.begin(), race.end(), race.begin(), ::tolower);

			// Check if the input race matches the one read from the file
			if (race == raceFromFile) {
				hp = hpFromFile;
				maxHealth = hpFromFile;
				attack = attackFromFile;
				defence = defenceFromFile;
				validRace = true;
				break;
			}
		}

		// Close the file
		file.close();
	}
	else {
		std::cout << "Unable to open stats.txt" << std::endl;
		Sleep(2000);
		//return; // Exit the function if the file cannot be opened
	}

	// If the race is not found, default to Human
	if (!validRace) {
		std::cout << "Invalid race choice. You will be a Human" << std::endl;
		race = "Human";
		hp = 30;
		maxHealth= 30;
		attack = 4;
		defence = 3;
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
			Sleep(500);
			break;
		}
		Sleep(400);
		system("cls");
		counter++;
	}

	name[0] = toupper(name[0]);
	race[0] = toupper(race[0]);
	sex[0] = toupper(sex[0]);
	//totalHealth = hp;
	//maxHealth = totalHealth;
}
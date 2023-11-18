#include "Character.h"
using namespace std;

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
	::string raceFromFile;
	int hpFromFile, attackFromFile, defenceFromFile;

	//player information for character creation
	::cout << "Enter Character's name: ";
	::getline(::cin, name);


	::cout << "Enter Character's class\n";
	::cout << "Elf\n";
	::cout << "Viking\n";
	::cout << "Goblin\n";
	::cout << "Wizard\n";
	::cout << "Ogre\n";
	::cout << "Type your class below: \n\n";
	::getline(::cin, race);


	::transform(race.begin(), race.end(), race.begin(), ::tolower); // Convert the input to lowercase

	::ifstream file("stats.txt");


	if (file.is_open()) {
		while (file >> raceFromFile >> hpFromFile >> attackFromFile >> defenceFromFile) 
		{
			// Convert the race input to lowercase
			::transform(race.begin(), race.end(), race.begin(), ::tolower);

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
		::cout << "Unable to open stats.txt" << ::endl;
		Sleep(2000);
		//return; // Exit the function if the file cannot be opened
	}

	// If the race is not found, default to Human
	if (!validRace) {
		::cout << "Invalid race choice. You will be a Human" << ::endl;
		race = "Human";
		hp = 30;
		maxHealth= 30;
		attack = 6;
		defence = 3;
	}



	::cout << "\n";
	::cout << "Enter Character's sex: ";
	::getline(::cin, sex);

	// Loading screen 
	system("cls");
	Sleep(200);
	for (int i = 0; i <= counter; i++)
	{

		if (i == 0)
		{
			::cout << "Creating Character.\n";
			::cout << "---->                   O\n";

		}
		if (i == 1)
		{
			::cout << "Creating Character..\n";
			::cout << "--------------->        O\n";
		}
		if (i == 2)
		{
			::cout << "Creating Character...\n";
			::cout << "----------------------->O\n";
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
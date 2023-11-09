
#include "Character.h"


void HUD();
void Intro();
void Combat();
void CombatHUD();
void Moving();
void CreateMonster();
void LevelUp();


int monsterHp = 0, monsterExp = 0, monsterLevel = 0, monsterAttack = 0, monsterHeal = 0, monsterSlain = 0;
bool hasRested = false;
bool bossActive = false;
bool choiceMade = false;
std::string monsterName[] = { "Witch", "Demon", "Hellhound", "Centaur", "Vampire" };
std::string boss = "Dragon";
int currentMonsterNames = 5;
std::string currentMonster = " ";

int counter = 0;

Character character;

int main()
{

	character.CharacterCreation();
	Intro();
	HUD();
	Moving();

	system("pause");
	return 0;
}




void type_text(const std::string& text)
{
	// loop through each character in the text
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		// output one character
		// flush to make sure the output is not delayed
		std::cout << text[i] << std::flush;

		// sleep 60 milliseconds
		Sleep(50); // use Sleep on windows
	}
}

void Intro()
{
	system("cls");
	//type_text("Welcome to The Dragon's Den. ");
	type_text("In the depths of a dangerous cavern, you must face a horde of creatures and monsters of all sizes. Each vanquished beast brings you closer to the fearsome Dragon.");
}

void HUD()
{
	//The UI that shows throughout the game
	Sleep(3000);
	system("cls");
	if (character.hp <= 0)
	{
		character.hp = 0;
	}
	std::cout << "Name: " << character.name << "\nHealth: " << character.hp << "\nRace: " << character.race << "\nSex: " << character.sex
		<< "\nLevel: " << character.level << "\nXP: " << character.currentXp << "\nXP to Level Up: " << character.xpToLevel << std::endl;
	Moving();
}

void CombatHUD()
{
	Sleep(500);
	system("cls");
	if (character.hp <= 0)
	{
		character.hp = 0;
	}
	std::cout << "Name:	" << character.name
		<< "		|		Monster Name: " << currentMonster
		<< "\nHealth: " << character.totalHealth
		<< "		|		Monster Health: " << monsterHp
		<< "\nLevel: " << character.level
		<< "		|		Monster Level : " << monsterLevel
		<< "	\nAttack: " << character.attack
		<< "		|		Monster Attack: " << monsterAttack
		<< " \nDefense: " << character.defence
		<< std::endl;

}

void Combat()	
{
	CombatHUD();
	int playerAction;
	int playerDamage = character.attack;
	//monsterAttack = 6 * monsterLevel / 2;


	if (character.totalHealth >= 1 && monsterHp >= 1)
	{
		std::cout << "\n";
		std::cout << "1. Attack\n";
		std::cout << "2. Guard\n";
		std::cout << "3. Flee\n";
		std::cout << "\n";
		std::cin >> playerAction;

		// if player attacks
		if (playerAction == 1)
		{
			std::cout << "Attacking!... You did " << playerDamage << " damage to " << currentMonster << std::endl;
			monsterHp = monsterHp - playerDamage;
			Sleep(3000);
			CombatHUD();
			if (monsterHp >= 1)
			{
				std::cout << "\n";
				std::cout << currentMonster << " is Attacking!.. \n";
				int damageTaken = monsterAttack - character.defence;
				if (damageTaken > 0) {
					character.hp -= damageTaken;
				}
				else if (damageTaken <= 0)
				{
					character.hp -= damageTaken;
				}
				else {
					// If the character's defense is higher than the monster's attack, no damage is taken.
				}
				if (character.totalHealth <= 0)
				{
					std::cout << "You took " << damageTaken << " damage. Your health is now 0  " << std::endl;
				}
				else
				{
					std::cout << "You took " << damageTaken << " damage. Your health is now " << character.totalHealth << std::endl;
				}
				hasRested = false;
				// if monster is Vampire, they can restore health upon attacking
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					std::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << std::endl;
				}
				// Change to function
				if (character.totalHealth <= 0)
				{
					character.totalHealth = 0;
					Sleep(2000);
					system("cls");
					std::cout << "You died :(\nYou were level " << character.level << ". You were killed by a level " << monsterLevel << " " << currentMonster << std::endl;
					Sleep(2000);
					exit(0);
				}

			}
			else if (monsterHp <= 0)
			{
				CombatHUD();
				monsterHp = 0;
				CombatHUD();
				Sleep(3000);
				std::cout << "\n";
				std::cout << "You defeated " << currentMonster << ". You gained " << monsterExp << " XP\nCongratulations!";
				monsterSlain++;
				hasRested = false;
				if (character.level != character.maxLevel)
				{
					character.currentXp = character.currentXp + monsterExp;
					LevelUp();
				}
				Sleep(2000);
				HUD();
			}
			Sleep(2000);
			Combat();
			
		}
		// if player defends
		else if (playerAction == 2)
		{
			std::cout << "Blocking\n";
			int i = rand() % 100 + 1;
			if (i >= 50)
			{
				std::cout << "You successfully Blocked the incoming Attack!\n";
				character.heal = 5;
				std::cout << "You managed to Heal whilst Guarding for " << character.heal << std::endl;
				character.totalHealth = character.totalHealth + character.heal;
				Sleep(2000);
				Combat();
			}
			else
			{
				std::cout << "You failed to Block the incoming Attack!\n";
				character.totalHealth = character.totalHealth - monsterAttack;
				std::cout << "You were Attacked from behind from failing to Block and suffered " << monsterAttack << " .Your Current HP is " << character.totalHealth << std::endl;
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					std::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << std::endl;
				}
				Sleep(2000);
				Combat();
			}
			if (character.totalHealth <= 0)
			{
				character.totalHealth = 0;
				Sleep(2000);
				system("cls");
				std::cout << "You died :(\nYou were level " << character.level << ". You were killed by a level " << monsterLevel << " " << currentMonster << std::endl;
				Sleep(2000);
				exit(0);
			}
			hasRested = false;
		}
		// if player runs
		else if (playerAction == 3)
		{
			std::cout << "You attempt to Run\n";
			int x = rand() % 100 + 1;
			if (x >= 50)
			{
				std::cout << "You successfully Ran away";
				HUD();
			}
			else
			{
				std::cout << "You failed to Run\n";
				std::cout << currentMonster << " Attacks you as you try to Run!\n";
				character.totalHealth -= monsterAttack + 10;
				std::cout << "You took " << monsterAttack + 10 << " Damage! Your current Health is " << character.totalHealth << std::endl;
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					std::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << std::endl;
				}
				Sleep(3000);
				Combat();
			}
			if (character.totalHealth <= 0)
			{
				character.totalHealth = 0;
				Sleep(2000);
				system("cls");
				std::cout << "You died :(\nYou were level " << character.level << ". You were killed by a level " << monsterLevel << " " << currentMonster << std::endl;
				Sleep(2000);
				exit(0);
			}
			hasRested = false;
		}
		// Invalid action
		else
		{
			std::cout << "Invalid Action";
			Sleep(500);
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			Combat();
		}

	}

}

void Moving()
{
	int choice;
	int temp;

	std::cout << "\n\n";
	std::cout << "1. Move forward\n";
	std::cout << "2. Rest\n";
	std::cout << "3. Move backwards\n";
	std::cout << "\n";

	while (!choiceMade)
	{
		// Read user input as a string
		std::string input;
		std::cin >> input;

		// Attempt to convert the input string to an integer
		if (isdigit(input[0])) {
			choice = std::stoi(input);

			if (choice == 1) {
				temp = (rand() % 100) + 1;
				std::cout << "You move forward...\n";
				if (temp >= 50) {
					// Encountering a monster
					CreateMonster(); 
					std::string currentMonster = "SomeMonster"; 
					std::cout << "A " << currentMonster << " appears! Prepare to fight!\n";
					Sleep(3000);
					hasRested = false;
					Combat(); 
				}
				else {
					std::cout << "You move forward and find nothing of interest.\n";
					HUD(); 
				}
				choiceMade = true;
			}
			else if (choice == 2) {
				if (!hasRested)
				{
					std::cout << "You set up camp and rest for the night\n";
					if (character.hp <= character.maxHealth)
					{
						character.heal = character.level * 10 / 2;
						//character.totalHealth = character.totalHealth + 10 * character.level;
						character.hp += character.heal;
					}
					std::cout << "By resting, you healed up, your current health is now " << character.totalHealth << std::endl;
					Sleep(3000);
					hasRested = true;
					HUD();
				}
				else {
					std::cout << "I have already rested today, I must venture onwards" << std::endl;
					HUD(); // Call your HUD function
				}
				choiceMade = true;
			}
			else if (choice == 3) {
				temp = (rand() % 100) + 1;
				std::cout << "You move backwards...\n";
				if (temp >= 50) {
					// Encountering a monster
					CreateMonster(); // Call your CreateMonster function
					std::string tempName = "AnotherMonster"; // Update with the generated monster name
					std::cout << "A " << tempName << " appears! Prepare to fight!\n";
					currentMonster = tempName; // Update the current monster name
					temp = 0;
					Sleep(3000);
					Combat(); // Call your Combat function
				}
				else {
					std::cout << "You find nothing of worth\n";
					hasRested = false; // Commented out in your code; uncomment if necessary
					HUD(); // Call your HUD function
				}
			}
			else
			{
				std::cout << "Invalid Choice\n" << std::endl;
				/*Sleep(500);
				isValid = false;
				Moving();*/
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
			choiceMade = true;
		}
		std::cout << "Invalid input. Please enter a valid integer choice.\n";
		choiceMade = false;
		
	}
}

void LevelUp()
{

	if (character.currentXp >= character.xpToLevel)
	{
		character.xpToLevel += floor(character.level + 25 * pow(2, character.level / 7));
		character.totalHealth = floor(character.totalHealth + 13 * pow(2, character.level / 8));

		if (character.level >= character.minLevel && character.level <= character.maxLevel)
		{
			character.level++;
			character.attack += 3;
			character.defence += 3;
		}
		else
		{
			character.level = 60;
		}
		character.maxHealth = character.totalHealth;
		std::cout << "You Levelled up! You are now level " << character.level << std::endl;
		std::cout << "Your Max HP has increased to " << character.totalHealth << std::endl;
		std::cout << "\n";
		Sleep(2000);
		LevelUp();
	}
	Sleep(3000);
	HUD();

}

void CreateMonster() {
	// Seed the random number generator
	std::srand(std::time(nullptr));

	// Generate a random index within the range of the monsterName array
	int randomIndex = std::rand() % (sizeof(monsterName) / sizeof(monsterName[0]));

	// Choose a random name from the array
	currentMonster = monsterName[randomIndex];

	monsterLevel = (rand() % (character.level + 1));

	monsterHp += monsterLevel;

	if (monsterSlain == 3)
	{
		currentMonster = "Dragon";
		bossActive = true;
		if (bossActive)
		{
			bossActive = false;
		}

	}
	if (currentMonster == "Witch")
	{
		monsterHp = 40;
		monsterAttack = 6 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Demon")
	{
		monsterHp = 30;
		monsterAttack = 8 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Hellhound")
	{
		monsterHp = 30;
		monsterAttack = 7 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Centaur")
	{
		monsterHp = 35 * (1 + (monsterLevel /10));
		monsterAttack = 4 * (1 + (monsterLevel / 10));
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Vampire")
	{
		monsterHp = 25;
		monsterAttack = 5 + monsterLevel;
		monsterHeal = 2 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Dragon")
	{
		monsterHp = 50;
		monsterAttack = 10 + monsterLevel;
		monsterExp = 10 * monsterLevel;
	}

	std::cout << "Created monster with name: " << currentMonster << std::endl;
	std::cout << "Monster HP: " << monsterHp << std::endl;
	std::cout << "Monster Level: " << monsterLevel << std::endl;
	std::cout << "Monster Attack: " << monsterAttack << std::endl;
	//std::cout << "Monster Experience: " << monsterExp << std::endl;
	Sleep(3000);
	Combat();
}




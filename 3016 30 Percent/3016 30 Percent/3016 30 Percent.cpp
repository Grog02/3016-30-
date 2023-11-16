
#include "Character.h"


void HUD();
void Intro();
void Outro();
void Combat();
void CombatHUD();
void Moving();
void CreateMonster();
void LevelUp();
void CheckHP();


int monsterHp = 0, monsterExp = 0, monsterLevel = 0, monsterAttack = 0, monsterDefence = 0, monsterHeal = 0, monsterSlain = 0;
bool hasRested = false;
bool bossActive = false;
bool bossSlain = false;
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
	type_text("Welcome to The Dragon's Den. ");
	type_text("You are a hero on a quest of obtaining a bountiful treasure guarded by a powerful Dragon!");
	type_text("In the depths of a dangerous cavern, you must face a horde of creatures and monsters of all sizes. Each vanquished beast brings you closer to the fearsome Dragon.");
}

void Outro()
{
	system("cls");
	type_text("You have slain the Dragon Boss ");
	type_text("In the depths of a dangerous cavern, you must face a horde of creatures and monsters of all sizes. Each vanquished beast brings you closer to the fearsome Dragon.");
}

void HUD()
{
	//The UI that shows throughout the game
	system("cls");
	if (character.hp <= 0)
	{
		character.hp = 0;
	}
	std::cout << "Name: " << character.name << "\nHealth: " << character.hp << "\nClass: " << character.race << "\nSex: " << character.sex
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
		<< "\nHealth: " << character.hp
		<< "		|		Monster Health: " << monsterHp
		<< "\nLevel: " << character.level
		<< "		|		Monster Level : " << monsterLevel
		<< "	\nAttack: " << character.attack
		<< "		|		Monster Attack: " << monsterAttack
		<< " \nDefense: " << character.defence
		<< "		|		Monster Defence: " << monsterDefence
		<< std::endl;

}

void Combat()	
{
	CombatHUD();
	int playerAction;
	int playerDamage = character.attack;
	CheckHP();

	if (character.hp >= 1 && monsterHp >= 1)
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
			int monsterDamageTaken = character.attack - monsterDefence;
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
					CheckHP();
				}
				else if (damageTaken <= 0)
				{
					std::cout << "The monster's attack could not penetrate your defence\n";
					damageTaken = 0;
				}
				else {
					// If the character's defense is higher than the monster's attack, no damage is taken.
				}
				if (character.hp <= 0)
				{
					std::cout << "You took " << damageTaken << " damage. Your health is now 0  " << std::endl;
				}
				else
				{
					std::cout << "You took " << damageTaken << " damage. Your health is now " << character.hp << std::endl;
				}
				hasRested = false;
				// if monster is Vampire, they can restore health upon attacking
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					std::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << std::endl;
				}

				CheckHP();


			}
			else if (monsterHp <= 0)
			{
				CombatHUD();
				monsterHp = 0;
				CombatHUD();
				Sleep(3000);
				std::cout << "\n";
				std::cout << "You defeated " << currentMonster << ". You gained " << monsterExp << " XP\nCongratulations!";
				//monsterSlain++;
				monsterSlain += 3;
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
				character.hp = character.hp+ character.heal;
				Sleep(2000);
				Combat();
			}
			else
			{
				std::cout << "You failed to Block the incoming Attack!\n";
				character.hp = character.hp - monsterAttack;
				std::cout << "You were Attacked from behind from failing to Block and suffered " << monsterAttack << " .Your Current HP is " << character.hp << std::endl;
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					std::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << std::endl;
				}
				Sleep(2000);
				Combat();
			}
			if (character.hp <= 0)
			{
				character.hp = 0;
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
				Sleep(2000);
				HUD();
			}
			else
			{
				std::cout << "You failed to Run\n";
				std::cout << currentMonster << " Attacks you as you try to Run!\n";
				character.hp -= monsterAttack + 10;
				std::cout << "You took " << monsterAttack + 10 << " Damage! Your current Health is " << character.hp << std::endl;
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					std::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << std::endl;
				}
				Sleep(3000);
				Combat();
			}
			if (character.hp <= 0)
			{
				character.hp = 0;
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
					Sleep(2000);
					HUD(); 
				}
				choiceMade = true;
			}
			else if (choice == 2) {
				if (!hasRested && character.hp < character.maxHealth)
				{
					std::cout << "You set up camp and rest for the night\n";
					Sleep(2000);
					if (character.hp <= character.maxHealth)
					{
						character.heal = character.level * 10 / 2;
						//character.totalHealth = character.totalHealth + 10 * character.level;
						character.hp += character.heal;
					}
					else
					{
						std::cout << "You cannot heal past your max health";
						Sleep(2000);
						HUD();
					}
					std::cout << "By resting, you healed up by " << character.heal << ", your current health is now " << character.hp << std::endl;
					Sleep(3000);
					hasRested = true;
					HUD();
				}
				else {
					std::cout << "I have already rested today, I must venture onwards" << std::endl;
					Sleep(2000);
					HUD(); // Call your HUD function

				}
				choiceMade = true;
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

void CheckHP()
{
	if (character.hp <= 0)
	{
		character.hp = 0;
		Sleep(2000);
		system("cls");
		std::cout << "You died :(\nYou were level " << character.level << ". You were killed by a level " << monsterLevel << " " << currentMonster << std::endl;
		Sleep(2000);
		exit(0);
	}
}
void LevelUp()
{
	int xpHeal;
		if (character.currentXp >= character.xpToLevel)
		{
			character.xpToLevel += floor(character.level + 25 * pow(2, character.level / 7));
			//character.hp = floor(character.hp + 13 * pow(2, character.level / 8));

			if (character.level >= character.minLevel && character.level <= character.maxLevel)
			{
				character.level++;
				character.attack += 3;
				character.defence += 1;
				character.maxHealth = floor(character.maxHealth + 13 * pow(2, character.level / 8));
				xpHeal = character.maxHealth - character.hp;
				character.hp += xpHeal;

			}
			else
			{
				character.level = 10;
			}

			std::cout << "You Levelled up! You are now level " << character.level << std::endl;
			std::cout << "Your Max HP has increased to " << character.hp << std::endl;
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
	if (monsterLevel == 0)
	{
		monsterLevel++;
	}
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
		monsterHp = 40 + (monsterLevel * 5);
		monsterAttack = 6 + monsterLevel;
		monsterDefence = 1 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Demon")
	{
		monsterHp = 30 + (monsterLevel * 5);
		monsterAttack = 8 + monsterLevel;
		monsterDefence = 1 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Hellhound")
	{
		monsterHp = 30 + (monsterLevel * 5);
		monsterAttack = 7 + monsterLevel;
		monsterDefence = 1 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Centaur")
	{
		monsterHp = 35 + (monsterLevel * 5);
		monsterAttack = 4 * (1 + (monsterLevel / 10));
		monsterDefence = 1 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Vampire")
	{
		monsterHp = 25 + (monsterLevel * 5);
		monsterAttack = 5 + monsterLevel;
		monsterDefence = 1 + monsterLevel;
		monsterHeal = 2 + monsterLevel;
		monsterExp = 5 * monsterLevel;
	}
	else if (currentMonster == "Dragon")
	{
		monsterHp = 50 + (monsterLevel * 5);
		monsterAttack = 10 + monsterLevel;
		monsterDefence = 1 + monsterLevel;
		monsterExp = 10 * monsterLevel;
	}

	std::cout << "You Encountered a : " << currentMonster << std::endl;
	std::cout << "Monster HP: " << monsterHp << std::endl;
	std::cout << "Monster Level: " << monsterLevel << std::endl;
	std::cout << "Monster Attack: " << monsterAttack << std::endl;
	std::cout << "Monster Defence: " << monsterDefence << std::endl;
	Sleep(3000);
	Combat();
}





#include "Character.h"

using namespace std;

// Declaring functions
void HUD();
void SlowText(const string& text);
void Intro();
void Outro();
void Combat();
void CombatHUD();
void Moving();
void CreateMonster();
void LevelUp();
void CheckHP();
void CheckMonsterHP();

// Declaring Monster Stats 
int monsterHp = 0, monsterExp = 0, monsterLevel = 0, monsterAttack = 0, monsterDefence = 0, monsterHeal = 0, monsterSlain = 0;

// Declaring Actions 
bool hasRested = false;
bool bossActive = false;
bool bossSlain = false;
bool choiceMade = false;
string monsterName[] = { "Witch", "Demon", "Hellhound", "Centaur", "Vampire" };
string boss = "Dragon";
int currentMonsterNames = 5;
string currentMonster = " ";

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

void SlowText(const string& text)
{
	// loop through each character in the text
	for (size_t i = 0; i < text.size(); ++i)
	{
		::cout << text[i] << flush;
		Sleep(50); 
	}
}
// Text to be displayed as if typed out for both the Intro and Outro to the Game
void Intro()
{
	system("cls");
	SlowText("Welcome to The Dragon's Den.\n"); 
	SlowText("You are a hero on a quest of obtaining a bountiful treasure guarded by a powerful Dragon!\n");
	SlowText("In the depths of a dangerous cavern, you must face a horde of creatures and monsters of all sizes.\n");
	SlowText("Each vanquished beast brings you closer to the fearsome and powerful Dragon.\n");
	Sleep(2000);
}

void Outro()
{
	system("cls");
	SlowText("Congratulations Mighty Warrior! You have slain the mighty Dragon Boss.\n");
	SlowText("As the Dragon's last roar fades out and it slumps to the ground defeated, you face the treasure it once guarded.\n");
	SlowText("The treasure consists of beautiful rubies and jewels and they glisten as you claim the rewards.\n");
	SlowText("After pocketing the gems you triumphantly leave the Dungeon never to return...\n");
	Sleep(2000);
	exit(0);
}

void HUD()
{
	//The UI that shows throughout the game (unless in combat)
	system("cls");
	if (character.hp <= 0)
	{
		CheckHP();
	}
	::cout << "Name: " << character.name << "\nHealth: " << character.hp << "\nClass: " << character.race << "\nSex: " << character.sex
		<< "\nLevel: " << character.level << "\nXP: " << character.currentXp << "\nXP to Level Up: " << character.xpToLevel << endl;
	Moving();
}

void CombatHUD()
{
	// The UI that shows when the player is in combat
	Sleep(500);
	system("cls");
		if (character.hp <= 0)
	{
		CheckHP();
	}
	::cout << "Name:	" << character.name
		<< "		|		Monster Name: " << currentMonster
		<< "\nHealth: " << character.hp
		<< "		|		Monster Health: " << monsterHp
		<< "\nLevel: " << character.level
		<< "		|		Monster Level : " << monsterLevel
		<< "	\nAttack: " << character.attack
		<< "		|		Monster Attack: " << monsterAttack
		<< " \nDefense: " << character.defence
		<< "		|		Monster Defence: " << monsterDefence
		<< endl;

}

void Combat()	
{
	CombatHUD();
	int playerAction;
	CheckHP();

	if (character.hp >= 1 && monsterHp >= 1)
	{
		::cout << "\n";
		::cout << "1. Attack\n";
		::cout << "2. Guard\n";
		::cout << "3. Flee\n";
		::cout << "\n";
		cin >> playerAction;

		// if player attacks
		if (playerAction == 1)
		{

			int monsterDamageTaken = character.attack - monsterDefence;
			if (monsterDamageTaken > 0) {
				monsterHp = monsterHp -  monsterDamageTaken;
			}
			else
			{
				monsterHp = monsterHp - character.attack;
			}	
			::cout << "Attacking!... You did " << monsterDamageTaken << " damage to " << currentMonster << endl;
			//CheckMonsterHP();
			Sleep(2000);

			CombatHUD();
			//Sleep(3000);
			if (monsterHp >= 1)
			{
				// if monster is not dead, it can attack
				::cout << "\n";
				::cout << currentMonster << " is Attacking!.. \n";
				// if player's defence is higher than monster's attack then the monster deals no damage
				int damageTaken = monsterAttack - character.defence;
				if (damageTaken > 0) {
					character.hp -= damageTaken;
					CheckHP();
				}
				else if (damageTaken <= 0)
				{
					::cout << "The monster's attack could not penetrate your defence\n";
					damageTaken = 0;
				}
				if (character.hp <= 0)
				{
					::cout << "You took " << damageTaken << " damage. Your health is now 0  " << endl;
				}
				else
				{
					::cout << "You took " << damageTaken << " damage. Your health is now " << character.hp << endl;
				}
				hasRested = false;
				// if monster is Vampire, they can restore health after attacking
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << endl;
				}
				CheckHP();
			}
			else if (monsterHp <= 0)
			{
				CheckMonsterHP();
			}
			Sleep(2000);
			Combat();
			
		}
		// if player attempts to guard
		else if (playerAction == 2)
		{
			::cout << "Blocking\n";
			int i = rand() % 100 + 1;
			if (i >= 50)
			{
				::cout << "You successfully Blocked the incoming Attack!\n";
				character.heal = 5 * character.level;
				Sleep(2000);
				if (character.maxHealth == character.hp)
				{
					::cout << "You cannot heal as you are at full health" << endl;
				}
				else
				{
					if (character.race == "Wizard")
					{
						::cout << "You managed to Heal whilst Guarding for " << character.heal + 2<< endl;
						character.hp = character.hp + character.heal + 2;
					}
					else
					{
						::cout << "You managed to Heal whilst Guarding for " << character.heal << endl;
						character.hp = character.hp + character.heal;
					}
				}

				Sleep(2000);
				Combat();
			}
			else
			{
				// if player fails to block attack, they take extra damage and the defence stat is not used because of this
				::cout << "You failed to Block the incoming Attack!\n";
				character.hp = character.hp - monsterAttack;
				::cout << "You were Attacked from behind from failing to Block and suffered " << monsterAttack << " .Your Current HP is " << character.hp << endl;
				if (currentMonster == "Vampire")
				{
					monsterHp = monsterHp + monsterHeal;
					::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << endl;
				}
				Sleep(2000);
				Combat();
			}
			if (character.hp <= 0)
			{
				CheckHP();
			}
			hasRested = false;
		}
		// if player runs
		else if (playerAction == 3)
		{
			::cout << "You attempt to Run\n";
			int x = rand() % 100 + 1;
			if (x >= 50)
			{
				::cout << "You successfully Ran away";
				Sleep(2000);
				HUD();
			}
			else
			{
				if (currentMonster == "Dragon")
				{
					::cout << "You cannot run from the Dragon!";
				}
				else
				{
					::cout << "You failed to Run\n";
					::cout << currentMonster << " Attacks you as you try to Run!\n";
					character.hp -= monsterAttack + 5;
					if (character.hp <= 0)
					{
						::cout << "You took " << monsterAttack + 5 << " Damage! Your current Health is " << 0 << endl;
					}
					else
					{
						::cout << "You took " << monsterAttack + 5 << " Damage! Your current Health is " << character.hp << endl;
					}
					if (currentMonster == "Vampire")
					{
						monsterHp = monsterHp + monsterHeal;
						::cout << "The Vampire Drained your Health! They Healed for " << monsterHeal << "!" << endl;
					}
				}
				Sleep(3000);
				Combat();
			}
			if (character.hp <= 0)
			{
				CheckHP();
			}
			hasRested = false;
		}
		// Invalid action
		else
		{
			::cout << "Invalid Action";
			Sleep(500);
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			Combat();
		}

	}

}

void Moving()
{
	int choice;
	int temp;

	::cout << "\n\n";
	::cout << "1. Move forward\n";
	::cout << "2. Rest\n";
	::cout << "\n";

	while (!choiceMade)
	{
		string input;
		cin >> input;
		

		// convert input to int
		if (isdigit(input[0])) {
			choice = stoi(input);
			if (choice == 1) {
				//cin.ignore(INT_MAX, '\n');
				temp = (rand() % 100) + 1;
				::cout << "You move forward...\n";
				if (temp >= 50) {
					// Encountering a monster
					CreateMonster(); 
					string currentMonster = "SomeMonster"; 
					::cout << "A " << currentMonster << " appears! Prepare to fight!\n";
					Sleep(3000);
					hasRested = false;
					Combat(); 
				}
				else {
					::cout << "You move forward and find nothing of interest.\n";
					Sleep(2000);
					HUD(); 
				}
				choiceMade = true;
			}
			else if (choice == 2) {
				// Player can only rest after performing an action, this stops players abusing the heal option
				if (!hasRested && character.hp < character.maxHealth)
				{
					::cout << "You set up camp and rest for the night\n";
					Sleep(2000);
					if (character.hp <= character.maxHealth)
					{
						character.heal = character.level * 10 / 2;
						character.hp += character.heal;
					}
					else
					{
						::cout << "You cannot heal past your max health";
						Sleep(2000);
						HUD();
					}
					::cout << "By resting, you healed up by " << character.heal << ", your current health is now " << character.hp << endl;
					Sleep(3000);
					hasRested = true;
					HUD();
				}
				else {
					::cout << "I have already rested today, I must venture onwards" << endl;
					Sleep(2000);
					HUD(); 

				}
				choiceMade = true;
			}
			else
			{
				::cout << "Invalid Choice\n" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			choiceMade = true;
		}
		::cout << "Invalid input. Please enter a valid integer choice.\n";
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
		::cout << "You died :(\nYou were level " << character.level << ". You were killed by a level " << monsterLevel << " " << currentMonster << endl;
		::cout << "\nYou killed " << monsterSlain << " Monsters before being defeated" << endl;
		Sleep(2000);
		exit(0);
	}
}

void CheckMonsterHP()
{
	if (monsterHp <= 0)
	{
		monsterHp = 0;
		CombatHUD();
		Sleep(1000);
		::cout << "\n";
		::cout << "You defeated " << currentMonster << ". You gained " << monsterExp << " XP\nCongratulations!";
		monsterSlain++;
		hasRested = false;
		if (currentMonster == "Dragon")
		{
			Sleep(3000);
			Outro();
		}
	}
	else
	{
		CombatHUD();
	}

	if (character.level != character.maxLevel)
	{
		character.currentXp = character.currentXp + monsterExp;
		LevelUp();
	}
	Sleep(2000);
	HUD();
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
				character.attack = character.attack + 3;
				character.defence = character.defence + 1;
				character.maxHealth = floor(character.maxHealth + 13 * pow(2, character.level / 8));
				xpHeal = character.maxHealth - character.hp;
				character.hp += xpHeal;

			}
			else
			{
				character.level = 10;
			}

			::cout << "You Levelled up! You are now level " << character.level << endl;
			::cout << "Your Max HP has increased to " << character.hp << endl;
			::cout << "\n";
			Sleep(2000);
			LevelUp();
		}
	Sleep(3000);
	HUD();
}

void CreateMonster() {
	
	// Seed the Random Number Generator
	srand(time(nullptr));

	// Generate random index in the range of MonsterName array
	int randomIndex = rand() % (sizeof(monsterName) / sizeof(monsterName[0]));

	// Set this to the current monster
	currentMonster = monsterName[randomIndex];

	// generates number between 0 and Player level and checks if the level is 0 and adds 1
	monsterLevel = (rand() % (character.level + 1));
	if (monsterLevel == 0)
	{
		monsterLevel++;
	}
	monsterHp += monsterLevel;
 
	// if the player has slain enough monsters then they can face the boss
	if (monsterSlain == 5)
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
		monsterAttack = 5 + monsterLevel;
		monsterDefence = 2 + monsterLevel;
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
		monsterDefence = 3 + monsterLevel;
		monsterExp = 10 * monsterLevel;
	}

	if (currentMonster == "Dragon")
	{
		::cout << "The Mighty Dragon Boss appears! You must slay it in order to retrieve the treasure!\n";
	}
	::cout << "You Encountered a : " << currentMonster << endl;
	::cout << "Monster HP: " << monsterHp << endl;
	::cout << "Monster Level: " << monsterLevel << endl;
	::cout << "Monster Attack: " << monsterAttack << endl;
	::cout << "Monster Defence: " << monsterDefence << endl;
	Sleep(3000);
	Combat();
}




# 3016-30-
## State Machine Diagram
![image](https://github.com/Grog02/3016-30-/assets/91668510/b2a59a87-b719-4035-a188-3d5230cc4b5d)


# The Dragon's Den.

## The Game: 
The Dragon's Den is a text based RolePlaying Game (RPG). You are a hero on a quest to slay the Dragon and claim the treasure that it is guarding. 

## Gameplay: 
When the game starts, the player is instructed to choose their name, class and gender and then their character has been created. The classes are Elf, Viking, Goblin, Wizard, Ogre and Human.
Once this happens the player is shown a UI with their given stats and is able to venture forwards into the Dungeon or Resting which heals the player if they are not at full health and have completed a battle as it stops the player from constantly healing whenever they wish which adds difficulty to the game.
The player has to slay 5 monsters in order to face the final Dragon Boss. The player can level up and their stats will increase but the monster stats will scale up slightly as well. 


## How to Play:
The character creation section of the game requires basic keyboard input for choosing their name, class and gender. Once the character is created they can press either 1 to move forwards or 2 to rest
(explained in the Gameplay Section)
The game ends when the player either slays the Dragon or loses all of their HP.

## Error Handling
![image](https://github.com/Grog02/3016-30-/assets/91668510/e63908f2-7dbc-4f85-88b7-dabea7d649c6)

The Code here checks for the right input, if the user does not type 1,2 or 3 during combat then their input will be ignored and the game will still be awaiting the correct input.

![image](https://github.com/Grog02/3016-30-/assets/91668510/8016c070-725f-4e07-abc6-47c94deec608)

This code checks for the input during the Main HUD, if the player inputs a integer that is not available then it returns "Invalid Choice", if the user inputs a non-integer input then the code returns
Invalid input. Please enter a valid integer choice.

### Creating Character
![image](https://github.com/Grog02/3016-30-/assets/91668510/aefa3f77-cc41-49d8-8346-42f2ee2b2b85)

The first error handling section of this screenshot is for if the file cannot be found, the game shuts down. Also if the player inputs something that isn't in the available shown classes, they are given Human.

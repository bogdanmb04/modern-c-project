export module player;

//import characterSelector;

#include <iostream>
#include <utility>
#include <string>

 export class Player
{
private:
	std::string character;
	int score;
	std::pair<int, int> position;
	std::pair<int, int> initialPosition; 
	int lives;
//	CharacterSelector characterSelector;

public:
	Player(std::string charName, int initLives, std::pair<int, int> startPos)
		: character(std::move(charName)), score(0), position(startPos), initialPosition(startPos), lives(initLives) {}

	void shoot()
	{
		std::cout << character << "A player was shoot!\n";
	}

	void move(const char direction)
	{
		switch (direction)
		{
		case 'U': position.second -= 1;
			break;
		case 'D': position.second += 1;
			break;
		case 'L': position.first -= 1;
			break;
		case 'R': position.first += 1;
			break;
		default: std::cout << "Invalid direction!\n";
			return;
		}
		std::cout << character << "Moved at " << position.first << ";" << position.second << "\n";
	}

	int GetScore() const
	{
		return score;
	}

	int GetLives() const
	{
		return lives;
	}
	void addScore(int points) 
	{
		score += points;
	}
	void GetShoot()
	{
		if (lives > 0)
		{
			lives--;
			std::cout << character << "Was shoot. Remain lives:" << lives << "\n";
			if (lives>0)
			{
				position = initialPosition;
				std::cout << character << "Was reseted" << initialPosition.first << "," << initialPosition.second << std::endl;
			}
			else
			{
				std::cout << character << "Was eliminated!\n";
			}
		}
		
	}

	/*void selectCharacter(const std::string& newCharacter)
	{
		std::string selectedCharacter = characterSelector.selectCharacter(newCharacter);
		if (!selectedCharacter.empty())
		{
			character = selectedCharacter;
			std::cout << "The selected character is: " << character << "\n";
		}
		else
		{
			std::cout << "Unavailable character\n";
		}
	}*/

	std::pair<int, int> getPosition() const
	{
		return position;
	}

	
};
#include "player.h"
import <iostream>;


void shoot()
{
	//std::cout << character << "A player was shoot!\n";
}


uint16_t Player::GetScore()
{
	return m_score;
}

uint8_t Player::GetLives()
{
	return m_lives;
}

void Player::AddScore(uint8_t points){
	m_score += points;
}



void GetShoot()
{
	/*if (lives > 0)
	{
		lives--;
		std::cout << character << "Was shoot. Remain lives:" << lives << "\n";
		if (lives > 0)
		{
			position = initialPosition;
			std::cout << character << "Was reseted" << initialPosition.first << "," << initialPosition.second << std::endl;
		}
		else
		{
			std::cout << character << "Was eliminated!\n";
		}
	}*/

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


void move(const char direction){
	/*switch (direction)
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
	std::cout << character << "Moved at " << position.first << ";" << position.second << "\n";*/
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

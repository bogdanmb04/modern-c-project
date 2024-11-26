#include "player.h"
#include <iostream>

void shoot()
{
	//std::cout << character << "A player was shoot!\n";
}


void Player::MoveUp() {
	position.second--;
	std::cout << "Moved Up to (" << position.first << ", " << position.second << ")\n";
}

void Player::MoveDown() {
	position.second++;
	std::cout << "Moved Down to (" << position.first << ", " << position.second << ")\n";
}

void Player::MoveLeft() {
	position.first--;
	std::cout << "Moved Left to (" << position.first << ", " << position.second << ")\n";
}

void Player::MoveRight() {
	position.first++;
	std::cout << "Moved Right to (" << position.first << ", " << position.second << ")\n";
}

uint16_t Player::GetScore()
{
	return m_score;
}

uint8_t Player::GetLives()
{
	return m_lives;
}

std::pair<uint16_t, uint16_t> Player::GetPosition()
{
	return position;
}

std::pair<uint16_t, uint16_t> Player::SetPosition(uint16_t x, uint16_t y)
{
	return position = std::make_pair(x, y);
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

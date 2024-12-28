#include "Player.h"
#include "database.h"
#include <iostream>

using namespace game;

void Shoot()
{
	//std::cout << character << "A player was shot!\n";
}

uint16_t Player::GetScore() const
{
	return m_score;
}

uint8_t Player::GetLives() const
{
	return m_lives;
}

uint32_t Player::GetID() const
{
	return m_id;
}

Direction Player::GetDirection() const
{
	return m_direction;
}

std::chrono::milliseconds Player::GetWeaponWaitTime() const
{
	std::chrono::milliseconds duration{ m_weapon.GetWaitTime() };
	return duration;
}

void Player::SetDirection(Direction direction)
{
	m_direction = direction;
}

void Player::AddScore(uint8_t points)
{
	m_score += points;
}

Player::Player(const User& user, const Weapon& weapon)
	: m_id{ user.GetID() }
	, m_score{ 0 }
	, m_lives{ 3 }
	, m_direction {Direction::UP}
	, m_weapon{ weapon }
{
	//EMPTY
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

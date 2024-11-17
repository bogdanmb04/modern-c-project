/**/export module player;
export module player;
export import characters;
export import bullet;

import movable;
import <iostream>;
using std::uint16_t;
using std::uint8_t;

#include <iostream>
#include <utility>
#include <string>
import entity;
 export class Player:public Entity
{
public:
	void Shoot();
	void Move();
	uint16_t GetScore() const;
	uint8_t GetLives() const;
	void AddScore(uint8_t points) const;
	void GetShoot();

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

	
public:
	Player(Player&&) noexcept = default;
	Player& operator =(Player&&) noexcept = default;
private:
	//game::Character m_character;
	uint16_t m_score;
	uint8_t m_lives;
	uint8_t m_direction : 2;
};
#pragma once

#include "user.h"
#include "entity.h"
#include <iostream>
#include <utility>
#include <string>
#include "movable.h"

using namespace user;

class Player : public User, public IMovable, public Entity
{
public:
	uint16_t GetScore();
	uint8_t GetLives();
	void Shoot();
	void AddScore(uint8_t points);
	void Move() override 
	{
		std::cout << "Player is moving" << std::endl;
	}

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
public:
	Player() = default;
	Player(Player&&) noexcept = default;
	Player& operator =(Player&&) noexcept = default;
private:
	//game::Character m_character;
	uint16_t m_score;
	uint8_t m_lives = 3;
	uint8_t m_direction : 2;
};
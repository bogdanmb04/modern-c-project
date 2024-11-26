#pragma once

#include "entity.h"

#include <iostream>
#include <utility>
#include <string>
#include "movable.h"

class Player : public Entity, IMovable
{
public:
	uint16_t GetScore();
	uint8_t GetLives();
	std::pair<uint16_t, uint16_t> GetPosition();

	std::pair<uint16_t, uint16_t> SetPosition(uint16_t x, uint16_t y);

	void Shoot();
	void AddScore(uint8_t points);
	void GetShoot();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void Move() override {
		std::cout << "Player is moving" << std::endl;
	}

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
#pragma once

#include "entity.h"

import <iostream>;
import <utility>;
import <string>;
import "movable.h";

class Player : public Entity, IMovable
{
public:
	void Shoot();
	void Move();
	uint16_t GetScore();
	uint8_t GetLives();
	void AddScore(uint8_t points);
	void GetShoot();



public:
	Player(Player&&) noexcept = default;
	Player& operator =(Player&&) noexcept = default;
private:
	//game::Character m_character;
	uint16_t m_score;
	uint8_t m_lives = 3;
	uint8_t m_direction : 2;
};
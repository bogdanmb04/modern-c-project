#pragma once

#include "user.h"
#include "entity.h"
#include <iostream>
#include <utility>
#include <string>
#include "movable.h"
#include "weapon.h"

using namespace user;

class Player : public IMovable, public Entity
{
public:
	uint16_t GetScore() const;
	uint8_t GetLives() const;
	uint32_t GetID() const;
	void Shoot();
	void AddScore(uint8_t points);
public:
	Player();
	Player(const User& user);
	Player(uint32_t ID);
	Player(Player&&) noexcept = default;
	Player& operator =(Player&&) noexcept = default;
private:
	//game::Character m_character;
	uint32_t m_id;
	uint16_t m_score;
	uint8_t m_lives : 2;
	Direction m_direction : 2;
	Weapon m_weapon;
};
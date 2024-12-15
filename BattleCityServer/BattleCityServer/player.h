#pragma once

#include "User.h"
#include "Entity.h"
#include "Movable.h"
#include "Weapon.h"
#include "Timer.h"
#include <iostream>
#include <utility>
#include <string>

using namespace user;

namespace game 
{

	class Player : public Entity
	{
	public:
		uint16_t GetScore() const;
		uint8_t GetLives() const;
		uint32_t GetID() const;
		Direction GetDirection() const;
		const std::chrono::milliseconds& GetWeaponWaitTime() const;
		void SetDirection(Direction direction);
		void AddScore(uint8_t points);

	public:
		Player() = default;
		Player(const User& user);
		Player(uint32_t ID);

	private:
		//game::Character m_character;
		uint32_t m_id;
		uint16_t m_score;
		uint8_t m_lives : 2;
		Direction m_direction : 2;
		Weapon m_weapon;
		Timer m_timer;
	};
}
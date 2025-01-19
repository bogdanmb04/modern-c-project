#pragma once

#include "User.h"
#include "Entity.h"
#include "Movable.h"
#include "Weapon.h"
#include "Timer.h"
#include "database.h"
#include <iostream>
#include <utility>
#include <string>
#include "map.h"

using namespace user;

namespace game 
{

	class Player : public Entity
	{
	public:
		const static int kInitialLivesNumber{ 3 };

	public:
		uint16_t GetScore() const;
		uint8_t GetLives() const;
		uint32_t GetID() const;
		Direction GetDirection() const;
		const Weapon& GetWeapon() const;
		const std::pair<size_t, size_t>& GetStartingPosition() const;
		void SetDirection(Direction direction);
		void AddScore(uint8_t points);
		void DecreaseLives();

	public:
		Player(const User& user, Weapon&& weapon);
		Player() = default;

	private:
		//game::Character m_character;
		uint32_t m_id;
		uint16_t m_score;
		uint8_t m_lives : 2;
		Direction m_direction : 2;
		Weapon m_weapon;
		Timer m_timer;
		std::pair<size_t, size_t> m_startingPosition;
	};
}
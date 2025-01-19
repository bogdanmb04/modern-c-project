#include "Player.h"
#include "database.h"
#include <iostream>

using namespace game;

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

const Weapon& game::Player::GetWeapon() const
{
	return m_weapon;
}

void Player::SetDirection(Direction direction)
{
	m_direction = direction;
}

void Player::AddScore(uint8_t points)
{
	m_score += points;
}

Player::Player(const User& user, Weapon&& weapon)
	: m_id{ user.GetID() }
	, m_score{ 0 }
	, m_lives{ 3 }
	, m_direction {Direction::UP}
	, m_weapon{ std::move(weapon) }
{
	//EMPTY
}

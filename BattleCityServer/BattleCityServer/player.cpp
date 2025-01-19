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

const Weapon& Player::GetWeapon() const
{
	return m_weapon;
}

const std::pair<size_t, size_t>& Player::GetStartingPosition() const
{
	return m_startingPosition;
}

void Player::SetDirection(Direction direction)
{
	m_direction = direction;
}

void Player::AddScore(uint8_t points)
{
	m_score += points;
}

void Player::DecreaseLives()
{
	m_lives--;
}

Player::Player(const User& user, Weapon&& weapon)
	: m_id{ user.GetID() }
	, m_score{ 0 }
	, m_lives{ kInitialLivesNumber }
	, m_direction {Direction::UP}
	, m_weapon{ std::move(weapon) }
	, m_startingPosition{ Map::Position{0, 0} }
{
	//EMPTY
}

#include "Bullet.h"

using namespace game;

Bullet::Bullet(Direction direction, std::chrono::milliseconds speed)
	: m_direction {direction}
	, m_speed {speed}
{/*EMPTY*/}

Direction game::Bullet::GetDirection() const
{
	return m_direction;
}

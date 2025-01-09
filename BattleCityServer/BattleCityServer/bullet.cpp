#include "Bullet.h"

using namespace game;

Bullet::Bullet(const Player& player)
	: m_direction {player.GetDirection()}
	, m_speed {player.GetWeapon().GetBulletSpeed()}
	, m_timer{}
{/*EMPTY*/}

Direction game::Bullet::GetDirection() const
{
	return m_direction;
}

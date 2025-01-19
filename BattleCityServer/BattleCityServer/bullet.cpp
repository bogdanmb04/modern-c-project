#include "Bullet.h"

using namespace game;

Bullet::Bullet(const Player& player)
	: m_direction {player.GetDirection()}
	, m_speed {player.GetWeapon().GetBulletSpeed()}
	, m_speedBuildUp{ 0.0 }
	, m_timer{}
	, Entity{GetPositionAfterDirection(player.GetPosition(), player.GetDirection())}
{/*EMPTY*/}


Direction game::Bullet::GetDirection() const
{
	return m_direction;
}

double Bullet::GetSpeed() const
{
	return m_speed;
}

double game::Bullet::GetSpeedBuildUp() const
{
	return m_speedBuildUp;
}

void game::Bullet::AddSpeedBuildUp()
{
	m_speedBuildUp += m_speed;
	m_timer.Restart();
}

void game::Bullet::ResetSpeedBuildUp()
{
	m_speedBuildUp = 0.0;
}

const Timer& Bullet::GetTimer() const
{
	return m_timer;
}



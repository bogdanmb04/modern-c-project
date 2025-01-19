#include "Bullet.h"

using namespace game;

Bullet::Bullet(const Player& player)
	: m_direction {player.GetDirection()}
	, m_speed {player.GetWeapon().GetBulletSpeed()}
	, m_speedBuildUp{ 0.0 }
	, m_timeOfLastSpeedUp{}
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

std::chrono::steady_clock Bullet::GetTimeOfLastSpeedUp() const
{
	return m_timeOfLastSpeedUp;
}

double Bullet::GetTimeDifference() const
{
	std::chrono::duration<double> diff = std::chrono::steady_clock::now() - m_timeOfLastSpeedUp.now();
	return diff.count();
}

void game::Bullet::AddSpeedBuildUp()
{
	m_speedBuildUp += m_speed;
}

void game::Bullet::ResetSpeedBuildUp()
{
	m_speedBuildUp = 0.0;
}


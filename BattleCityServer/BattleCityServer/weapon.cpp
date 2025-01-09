#include "Weapon.h"

Weapon::Weapon(uint32_t id, uint16_t bulletWaitTime, double bulletSpeed, uint32_t userID)
	: m_bulletWaitTime{ bulletWaitTime }
	, m_bulletSpeed{ bulletSpeed }
	, m_id{ id }
	, m_userID{ userID }
{
	/*EMPTY*/
}

Weapon::Weapon(uint32_t userID)
	: m_userID{userID}
	, m_bulletSpeed{ kDefaultBulletSpeed }
	, m_bulletWaitTime{ kDefaultBulletWaitTime }
{
	/*EMPTY*/
}

double Weapon::GetBulletSpeed() const
{
	return m_bulletSpeed;
}

uint16_t Weapon::GetBulletWaitTime() const
{
	return m_bulletWaitTime;
}

uint32_t Weapon::GetID() const
{
	return m_id;
}

uint32_t Weapon::GetUserID() const
{
	return m_userID;
}

std::chrono::milliseconds Weapon::GetBulletWaitTimeMilliseconds() const
{
	std::chrono::milliseconds duration{ this->GetBulletWaitTime()};
	return duration;
}

void Weapon::SetBulletSpeed(double speed)
{
	m_bulletSpeed = speed;
}

void Weapon::SetBulletWaitTime(uint16_t waitTime)
{
	m_bulletWaitTime = waitTime;
}

void Weapon::SetID(uint32_t id)
{
	m_id = id;
}

void Weapon::SetUserID(uint32_t userID)
{
	m_userID = userID;
}

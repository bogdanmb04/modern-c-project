#include "Weapon.h"

Weapon::Weapon(uint32_t id, uint32_t bulletWaitTime, uint16_t bulletSpeed, uint32_t userID)
	: m_bulletWaitTime{ bulletWaitTime }
	, m_bulletSpeed{ bulletSpeed }
	, m_id{ id }
	, m_userID{ userID }
{/*EMPTY*/
}

uint16_t Weapon::GetSpeed() const
{
	return m_bulletSpeed;
}

uint32_t Weapon::GetWaitTime() const
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

void Weapon::SetSpeed(uint16_t speed)
{
	m_bulletSpeed = speed;
}

void Weapon::SetWaitTime(uint32_t waitTime)
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

#include "weapon.h"

Weapon::Weapon(uint32_t id, const std::chrono::milliseconds& bulletWaitTime, uint16_t bulletSpeed, std::optional<uint32_t> userID = std::nullopt)
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

const std::chrono::milliseconds& Weapon::GetWaitTime() const
{
	return m_bulletWaitTime;
}

uint16_t Weapon::GetID() const
{
	return m_id;
}

const std::optional<uint32_t>& Weapon::GetUserID() const
{
	return m_userID;
}

void Weapon::SetSpeed(uint16_t speed)
{
	m_bulletSpeed = speed;
}

void Weapon::SetWaitTime(const std::chrono::milliseconds time)
{
	m_bulletWaitTime = time;
}

void Weapon::SetID(uint32_t id)
{
	m_id = id;
}

void Weapon::SetUserID(uint32_t userID)
{
	m_userID = userID;
}

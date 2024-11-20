#include "user.h"


user::User::User(const std::string& username, uint8_t totalScore, uint16_t specialMoney, const Weapon& weapon)
	: m_id(0)
	, m_username {username}
	, m_totalScore {totalScore}
	, m_specialMoney {specialMoney}
	, m_weapon {weapon}
{/*EMPTY*/}

std::string user::User::GetUsername() const
{
	return m_username;
}

uint8_t user::User::GetTotalScore() const
{
	return m_totalScore;
}

uint16_t user::User::GetSpecialMoney() const
{
	return m_specialMoney;
}

int user::User::GetId() const
{
    return m_id;
}

void user::User::SetId(int id)
{
	m_id = id;
}

void user::User::SetUsername(const std::string& username)
{
	m_username = username;
}

void user::User::SetTotalScore(uint8_t score)
{
	m_totalScore = score;
}

void user::User::SetSpecialMoney(uint16_t money)
{
	m_specialMoney = money;
}

std::ostream& user::operator<<(std::ostream& os, const User& user)
{
	return os << std::format("{} {} {}", user.GetUsername(), user.GetSpecialMoney(), user.GetTotalScore());
}


Weapon::Weapon(const std::chrono::milliseconds& bulletWaitTime, uint16_t bulletSpeed)
	: m_bulletWaitTime{ bulletWaitTime }
	, m_bulletSpeed{ bulletSpeed }
{/*EMPTY*/}







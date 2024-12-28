#include "User.h"

using namespace user;

User::User(uint32_t userID, const std::string& username, uint8_t totalScore, uint16_t specialMoney, uint32_t weaponID)
	: m_id{userID}
	, m_username {username}
	, m_totalScore {totalScore}
	, m_specialMoney {specialMoney}
	, m_weaponID {weaponID}
{/*EMPTY*/}

User::User(const std::string & username, const std::string & password)
	: m_id{}
	, m_username {username}
	, m_password {password}
	, m_totalScore{ 0 }
	, m_specialMoney{ 0 }
	, m_weaponID{}
{
	/*EMPTY*/
}

const std::string& user::User::GetUsername() const
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

uint32_t user::User::GetID() const
{
    return m_id;
}

uint32_t user::User::GetWeaponID() const
{
	return m_weaponID;
}

const std::string&  user::User::GetPassword() const
{
	return m_password;
}

void user::User::SetID(uint32_t id)
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

void user::User::SetWeaponID(uint32_t weaponID)
{
	m_weaponID = weaponID;
}

void user::User::SetPassword(const std::string& password)
{
	m_password = password;
}

std::ostream& user::operator<<(std::ostream& os, const User& user)
{
	return os << std::format("{} {} {}", 
		user.GetUsername(), 
		user.GetSpecialMoney(), 
		user.GetTotalScore());
}







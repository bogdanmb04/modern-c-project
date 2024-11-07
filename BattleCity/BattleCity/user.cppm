export module user;

import <iostream>;
import <chrono>;

using std::uint16_t;
using std::uint8_t;

//TODO: talk at lab about how to separate user and weapon modules without making a cyclic dependency :(
class Weapon
{
public:
	friend class User;

private:
	std::chrono::milliseconds m_bulletWaitTime;
	uint16_t m_bulletSpeed;
	Weapon(const std::chrono::milliseconds& bulletWaitTime, uint16_t bulletSpeed);
};

namespace user
{
	export class User
	{
	private:
		std::string m_username;
		uint8_t m_totalScore;
		uint16_t m_specialMoney;
		Weapon m_weapon;

	public:
		User(const std::string& username, uint8_t totalScore, uint16_t specialMoney, const Weapon& weapon);
		User(const User&) = delete;
		User& operator = (const User& other) = delete;

		std::string GetUsername() const;
		uint8_t GetTotalScore() const;
		uint16_t GetSpecialMoney() const;
	};

	export std::ostream& operator << (std::ostream& os, const User& user);

}

Weapon::Weapon(const std::chrono::milliseconds& bulletWaitTime, uint16_t bulletSpeed)
	: m_bulletWaitTime { bulletWaitTime }
	, m_bulletSpeed {bulletSpeed}
{/*EMPTY*/}
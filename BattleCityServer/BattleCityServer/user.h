#pragma once
//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
//#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

import <iostream>;
import <chrono>;
//import <sqlite_orm/sqlite_orm.h>;

using std::uint16_t;
using std::uint8_t;

//namespace sql = sqlite_orm;

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
	class User
	{
	private:
		int m_id;
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
		int GetId() const;

		void SetId(int id);
		void SetUsername(const std::string& username);
		void SetTotalScore(uint8_t score);
		void SetSpecialMoney(uint16_t money);
	};

	std::ostream& operator << (std::ostream& os, const User& user);

	/*inline auto CreateStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"Users",
				sql::make_column("id", &User::SetId, &User::GetId, sql::primary_key().autoincrement()),
				sql::make_column("username", &User::GetUsername, &User::SetUsername),
				sql::make_column("totalScore", &User::GetTotalScore, &User::SetTotalScore),
				sql::make_column("specialMoney", &User::GetSpecialMoney, &User::SetSpecialMoney)
			)
		);
	}*/
}
#pragma once
#include "weapon.h";

import <iostream>;
import <chrono>;

using std::uint16_t;
using std::uint8_t;


namespace user
{
	class User
	{

	public:
		User(const std::string& username, uint8_t totalScore, uint16_t specialMoney, const Weapon& weapon);
		User(const User&) = delete;
		User& operator = (const User& other) = delete;

		std::string GetUsername() const;
		uint8_t GetTotalScore() const;
		uint16_t GetSpecialMoney() const;
		int GetID() const;

		void SetID(int id);
		void SetUsername(const std::string& username);
		void SetTotalScore(uint8_t score);
		void SetSpecialMoney(uint16_t money);

	private:
		int m_id;
		std::string m_username;
		uint8_t m_totalScore;
		uint16_t m_specialMoney;
		Weapon m_weapon;
	};

	std::ostream& operator << (std::ostream& os, const User& user);
}
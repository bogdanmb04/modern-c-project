#pragma once
#include "Weapon.h"
#include <iostream>

using std::uint16_t;
using std::uint8_t;
using std::uint32_t;


namespace user
{
	class User
	{
	public:
		User(uint32_t userID, const std::string& username, uint8_t totalScore, uint16_t specialMoney, uint32_t weapon);
		User(const std::string& username, const std::string& password);
		User() = default;

		uint32_t GetID() const;
		const std::string& GetUsername() const;
		uint8_t GetTotalScore() const;
		uint16_t GetSpecialMoney() const;
		uint32_t GetWeaponID() const;
		const std::string& GetPassword() const;

		void SetID(uint32_t id);
		void SetUsername(const std::string& username);
		void SetTotalScore(uint8_t score);
		void SetSpecialMoney(uint16_t money);
		void SetWeaponID(uint32_t weaponID);
		void SetPassword(const std::string& password);

		void AddTotalScore(uint32_t amount);
		void AddSpecialMoney(uint32_t amount);

	private:
		uint32_t m_id; //PK
		std::string m_username;
		uint8_t m_totalScore;
		uint16_t m_specialMoney;
		uint32_t m_weaponID; //FK
		std::string m_password;
	};

	std::ostream& operator << (std::ostream& os, const User& user);
}
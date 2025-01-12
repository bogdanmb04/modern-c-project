#pragma once
#include <sqlite_orm/sqlite_orm.h>

#include "User.h"
#include "Weapon.h"

namespace sql = sqlite_orm;
using namespace user;

namespace server
{
	inline auto CreateDatabase(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"User",
				sql::make_column("id", &User::SetID, &User::GetID, sql::primary_key().autoincrement()),
				sql::make_column("username", &User::GetUsername, &User::SetUsername, sql::unique()),
				sql::make_column("totalScore", &User::GetTotalScore, &User::SetTotalScore),
				sql::make_column("specialMoney", &User::GetSpecialMoney, &User::SetSpecialMoney),
				sql::make_column("weaponID", &User::GetWeaponID, &User::SetWeaponID),
				sql::make_column("password", &User::GetPassword, &User::SetPassword)
			),
			sql::make_table(
				"Weapon",
				sql::make_column("id", &Weapon::SetID, &Weapon::GetID, sql::primary_key().autoincrement()),
				sql::make_column("bulletWaitTime", &Weapon::GetBulletWaitTime, &Weapon::SetBulletWaitTime),
				sql::make_column("bulletSpeed", &Weapon::GetBulletSpeed, &Weapon::SetBulletSpeed),
				sql::make_column("userID", &Weapon::GetUserID, &Weapon::SetUserID)
				
			)
		);
	}
	/*sql::foreign_key(&User::GetID).references(&Weapon::GetID)*/
	/*sql::foreign_key(&Weapon::GetUserID).references(&User::GetID)*/

	//https://sqliteorm.com/files/SQLITE_ORM%20Tutorial%204.3.pdf - see foreign key constraints!

	using Database = decltype(CreateDatabase(""));

	class GameDatabase
	{
	public:
		void Initialize();
		void AddUser(const User& user);
		bool RegisterUser(const std::string& username, const std::string& password);
		User GetUser(uint32_t id);
		User GetUserByUsername(const std::string& username);
		bool ValidateUserCredentials(const std::string& username, const std::string& password);
		bool UserExists(const std::string& username);

		void AddWeapon(const Weapon& weapon);
		Weapon GetWeapon(int userId);

		void UpgradeBulletWaitTime(uint32_t id);
		void UpgradeBulletSpeed(uint32_t id);

		Database& GetStorage();

	private:
		const std::string kDbFile{ "users.sqlite" };

	private:
		Database m_db = CreateDatabase(kDbFile);
	};
}
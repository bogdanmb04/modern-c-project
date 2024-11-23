#pragma once
#include <sqlite_orm/sqlite_orm.h>;
#include <crow.h>

import "user.h";
import "weapon.h";

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
				sql::make_column("username", &User::GetUsername, &User::SetUsername),
				sql::make_column("totalScore", &User::GetTotalScore, &User::SetTotalScore),
				sql::make_column("specialMoney", &User::GetSpecialMoney, &User::SetSpecialMoney)
			),
			sql::make_table(
				"Weapon",
				sql::make_column("id", &Weapon::SetID, &Weapon::GetID, sql::primary_key().autoincrement()),
				sql::make_column("bulletWaitTime", &Weapon::GetWaitTime, &Weapon::SetWaitTime),
				sql::make_column("bulletSpeed", &Weapon::GetSpeed, &Weapon::SetSpeed),
				sql::make_column("userID", &Weapon::GetUserID, &Weapon::SetUserID),
				sql::foreign_key(&Weapon::GetUserID).references(&User::GetID)
			)
		);
	}

	//https://sqliteorm.com/files/SQLITE_ORM%20Tutorial%202.7.pdf - see pages 58-60 for foreign key constraints!

	using Database = decltype(CreateDatabase(""));

	class GameDatabase
	{
		//TODO : Implement!!
	};
}
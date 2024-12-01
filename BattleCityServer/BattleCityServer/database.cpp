#include "database.h"

using namespace server;

void GameDatabase::Initialize()
{
	m_db.sync_schema();
}

void server::GameDatabase::AddUser(const User& user)
{
	m_db.insert(user);
}

User server::GameDatabase::GetUser(int id)
{
	return m_db.get<User>(id);
}

void server::GameDatabase::AddWeapon(const Weapon& weapon)
{
	m_db.insert(weapon);
}

std::vector<Weapon> server::GameDatabase::GetWeaponsByUser(int userId)
{
	return m_db.get_all<Weapon>(sql::where(sql::c(&Weapon::GetUserID) == userId));
}

Database& server::GameDatabase::GetStorage()
{
	return m_db;
}

bool server::GameDatabase::ValidateUserCredentials(const std::string& username, const std::string& password)
{
	auto users = m_db.get_all<User>(sql::where(sql::c(&User::GetUsername) == username && sql::c(&User::GetPassword) == password));
	return !users.empty();
}

User server::GameDatabase::GetUserByUsername(const std::string& username)
{
	return m_db.get<User>(sql::where(sql::c(&User::GetUsername) == username));
}

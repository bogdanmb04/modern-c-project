#include "Database.h"

using namespace server;

void GameDatabase::Initialize()
{
	m_db.sync_schema();
}

void GameDatabase::AddUser(const User& user)
{
	m_db.insert(user);
}

bool GameDatabase::RegisterUser(const std::string& username, const std::string& password)
{
	User user;
	user.SetUsername(username);
	user.SetPassword(password);
	m_db.insert(user);
	return true;
}

User GameDatabase::GetUser(uint32_t id)
{
	return m_db.get<User>(id);
}

void GameDatabase::AddWeapon(const Weapon& weapon)
{
	m_db.insert(weapon);
}

std::vector<Weapon> GameDatabase::GetWeaponsByUser(int userId)
{
	return m_db.get_all<Weapon>(sql::where(sql::c(&Weapon::GetUserID) == userId));
}

Database& GameDatabase::GetStorage()
{
	return m_db;
}

bool GameDatabase::ValidateUserCredentials(const std::string& username, const std::string& password)
{
	auto users = m_db.get_all<User>(sql::where(sql::c(&User::GetUsername) == username));
	if (!users.empty())
		return users[0].GetPassword() == password;
	return false;
}

bool GameDatabase::UserExists(const std::string& username)
{
	auto users = m_db.get_all<User>(sql::where(sql::c(&User::GetUsername) == username));
	return !users.empty();
}

User GameDatabase::GetUserByUsername(const std::string& username)
{
	return m_db.get_all<User>(sql::where(sql::c(&User::GetUsername) == username))[0];
}

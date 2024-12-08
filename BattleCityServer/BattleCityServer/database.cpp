#include "Database.h"

using namespace server;

void GameDatabase::Initialize()
{
	m_db.sync_schema();
}

void server::GameDatabase::AddUser(const User& user)
{
	m_db.insert(user);
}

bool server::GameDatabase::RegisterUser(const std::string& username, const std::string& password)
{
	User user;
	user.SetUsername(username);
	user.SetPassword(password);
	m_db.insert(user);
	return true;
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
	auto users = m_db.get_all<User>(sql::where(sql::c(&User::GetUsername) == username));
	if (!users.empty())
		return users[0].GetPassword() == password;
	return false;
}

bool server::GameDatabase::UserExists(const std::string& username)
{
	auto users = m_db.get_all<User>(sql::where(sql::c(&User::GetUsername) == username));
	return !users.empty();
}

User server::GameDatabase::GetUserByUsername(const std::string& username)
{
	return m_db.get<User>(sql::where(sql::c(&User::GetUsername) == username));
}

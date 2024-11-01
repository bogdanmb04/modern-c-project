module user;

using user::User;

User::User(const std::string& username, uint8_t totalScore, uint16_t specialMoney)
	: m_username{username}
	, m_totalScore {totalScore}
	, m_specialMoney {specialMoney}
{/*EMPTY*/}

std::string user::User::GetUsername() const
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

std::ostream& user::operator<<(std::ostream& os, const User& user)
{
	return os << std::format("{} {} {}", user.GetUsername(), user.GetSpecialMoney(), user.GetTotalScore());
}

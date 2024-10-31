module user;

using user::User;

User::User(const std::string& username, uint8_t totalScore, uint16_t specialMoney)
	: m_username{username}
	, m_totalScore {totalScore}
	, m_specialMoney {specialMoney}
{/*EMPTY*/}

void User::ViewStats(std::ostream& os)
{
	os << std::format("{} {} {}", m_username, m_totalScore, m_specialMoney);
}

void User::GoToShop()
{
}

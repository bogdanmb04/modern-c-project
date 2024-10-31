export module user;

import <iostream>;

using std::uint16_t;
using std::uint8_t;

namespace user
{
	export class User
	{
	private:
		std::string m_username;
		uint8_t m_totalScore;
		uint16_t m_specialMoney;

	public:
		User(const std::string& username, uint8_t totalScore, uint16_t specialMoney);
		User(const User&) = delete;
		User& operator = (const User& other) = delete;

		void ViewStats(std::ostream& os);
		void GoToShop();
	};

}
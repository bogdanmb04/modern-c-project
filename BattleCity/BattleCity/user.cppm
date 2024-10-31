export module user;

import <string>;
import <cstdint>;

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
		User(std::string username);
		void ViewStats();
		void GoToShop();
	};

}
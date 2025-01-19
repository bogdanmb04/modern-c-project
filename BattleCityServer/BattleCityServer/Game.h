#pragma once
#include "Map.h"
#include "Player.h"
#include "Database.h"
#include "Timer.h"
#include <ranges>

namespace game
{
	class Game
	{
	public:
		Game();
		~Game();
		void Run();
		void Initialize();
		void AddPlayer(Player& player);
		const Timer& GetTimer();
	public:
		inline static uint8_t kGameCounter{ 1 };
	private:
		Map m_map;
		std::array<std::shared_ptr<Player>, 4> m_players;
		Timer m_timer;
		Player m_playerToAdd;
	};
}


#pragma once
#include "Map.h"
#include "Player.h"
#include <ranges>

namespace game
{
	class Game
	{
	public:
		Game();
		void StartGame();
		void EndGame();
	private:
		Map m_map;
		std::array<std::shared_ptr<Player>, 4> m_players;
	};
}


#include "Game.h"

using namespace game;

Game::Game()
	: m_map{Map::Map()}
	, m_players{}
{
	kGameCounter += 1;
}

Game::~Game()
{
	if (kGameCounter >= 255)
		kGameCounter = 1;
}

void game::Game::AddPlayer(Player& player)
{
	auto ptrPlayer = std::make_shared<Player>(player);
	for (auto& elem : m_players)
	{
		if (elem == nullptr)
		{
			elem = ptrPlayer;
			return;
		}
	}
}

const Timer& game::Game::GetTimer()
{
	return m_timer;
}

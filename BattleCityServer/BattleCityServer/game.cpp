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

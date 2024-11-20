#include "map.h"

import <vector>;
import "powerup.h";

std::ostream& game::operator<<(std::ostream& out, const Map& map)
{

	out << "Map Dimensions: " << map.GetWidth() << " x " << map.GetHeight() << "\n";

	for (size_t x = 0; x < map.GetWidth(); ++x)
	{
		for (size_t y = 0; y < map.GetHeight(); ++y)
		{
			const Tile& tile = map.GetTile(x, y);
			switch (tile.GetType())
			{
			case Tile::TileType::Free:
				out << "F" << " ";
				break;
			case Tile::TileType::DestructibleWall:
				out << "D" << " ";
				break;
			case::Tile::TileType::IndestructibleWall:
				out << "I" << " ";
				break;
			}
		}
		out << std::endl;
	}

	return out;
}

game::Map::Map()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<size_t> widthDist(kWidthMin, kWidthMax);
	std::uniform_int_distribution<size_t> heightDist(kHeightMin, kHeightMax);

	m_width = widthDist(gen);
	m_height = heightDist(gen);

	////TODO: add conditions for tiles: how many, where and which type

	m_squares.resize(m_width);
	for (int i = 0; i < m_height; ++i)
	{
		m_squares.reserve(m_height);
	}

	for (size_t x = 0; x < m_width; ++x)
	{
		for (size_t y = 0; y < m_height; ++y)
		{
			//instead of equal chance for all tiles, 50% free, 45% destructible wall, 15% indestructible
			Tile::TileType type;
			std::uint8_t random = gen() % 100;
			if (random < 50)
				type = Tile::TileType::Free;
			else if (random >= 50 && random <= 85)
				type = Tile::TileType::DestructibleWall;
			else type = Tile::TileType::IndestructibleWall;
			m_squares[x].emplace_back(type, nullptr);
		}
	}

	//change corners to assure they are free
	m_squares[0][0].first.SetType(Tile::TileType::Free);
	m_squares[m_width - 1][0].first.SetType(Tile::TileType::Free);
	m_squares[0][m_height - 1].first.SetType(Tile::TileType::Free);
	m_squares[m_width - 1][m_height - 1].first.SetType(Tile::TileType::Free);
}

size_t game::Map::GetWidth() const
{
	return m_width;
}

size_t game::Map::GetHeight() const
{
	return m_height;
}

Tile game::Map::GetTile(size_t x, size_t y) const
{
	if (x >= m_width || y >= m_height || x < 0 || y < 0) {
		throw std::out_of_range("Tile coordinates are out of bounds");
	}
	return m_squares[x][y].first;
}

void game::Map::PlaceBombsOnWalls(std::vector<Bomb>& bombs)
{
	size_t no_bombs = kNoBombs;

	std::vector<Position> destructibleWalls;
	for (size_t y = 0; y < m_height; ++y)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			const Tile& tile = GetTile(x, y);
			if (tile.GetType() == Tile::TileType::DestructibleWall)
			{
				destructibleWalls.emplace_back(x, y);
			}
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(destructibleWalls.begin(), destructibleWalls.end(), gen);

	for (size_t i = 0; i < std::min(no_bombs, destructibleWalls.size()); ++i)
	{
		const auto& [x, y] = destructibleWalls[i];
		//bombs.emplace_back(std::make_pair(static_cast<uint16_t>(x), y));
		std::cout << "Placed bomb at (" << x << ", " << y << ")" << std::endl;
	}
}

void game::Map::placePlayer()
{
	if (m_width < 2 || m_height < 2) {
		throw std::runtime_error("Map dimensions are too small to place players in corners.");
	}

	std::cout << "Players placed in corners of the map." << std::endl;
}


namespace game {

	// Add a container for active power-ups
	std::vector<PowerUp> m_activePowerUps;

	// Example function to add a power-up
	void AddPowerUp(const PowerUp& powerUp) {
		m_activePowerUps.push_back(powerUp);
	}
}




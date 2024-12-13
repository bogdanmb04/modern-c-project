#include "Map.h"
#include <vector>
#include "PowerUp.h"

using namespace game;


const Map::Square& game::Map::operator[](const Position& pos) const
{
	const auto& [x, y] = pos;
	if (x >= m_width || y >= m_height || x < m_width || y < m_height)
	{
		throw std::out_of_range("Invalid position accessed");
	}
	return m_squares[y * m_height + x];
}

Map::Square& game::Map::operator[](const Position& pos)
{
	return const_cast<Map::Square&>(std::as_const(*this)[pos]);
}

std::ostream& game::operator<<(std::ostream& out, const Map& map)
{

	out << "Map Dimensions: " << map.GetWidth() << " x " << map.GetHeight() << "\n";

	for (size_t y = 0; y < map.GetHeight(); ++y)
	{
		for (size_t x = 0; x < map.GetWidth(); ++x)
		{
			const auto& square = map[{x, y}];
			const Tile& tile = square.first;
			const std::shared_ptr<Entity>& entity = square.second;

			if (entity != nullptr && dynamic_cast<Player*>(entity.get()))
			{
				out << "P" << " ";
			}
			else {
				switch (tile.GetType()) {
				case Tile::TileType::Free:
					out << "F" << " ";
					break;
				case Tile::TileType::DestructibleWall:
					out << "D" << " ";
					break;
				case Tile::TileType::IndestructibleWall:
					out << "I" << " ";
					break;
				}
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

	m_squares.reserve(m_width * m_height);

	for (size_t index = 0; index < m_height * m_width; ++index)
	{
		//instead of equal chance for all tiles, 50% free, 45% destructible wall, 15% indestructible
		Tile::TileType type;
		std::uint8_t random = gen() % 100;
		if (random < 50)
			type = Tile::TileType::Free;
		else if (random >= 50 && random <= 85)
			type = Tile::TileType::DestructibleWall;
		else type = Tile::TileType::IndestructibleWall;
		m_squares.emplace_back(type, nullptr);
	}

	//change corners to assure they are free
	m_squares.at(0).first.SetType(Tile::TileType::Free);
	m_squares.at(m_width - 1).first.SetType(Tile::TileType::Free);
	m_squares.at(m_height * (m_width - 1)).first.SetType(Tile::TileType::Free);
	m_squares.at(m_width * m_height - 1).first.SetType(Tile::TileType::Free);
}

const std::vector<Map::Square>& game::Map::GetSquares() const
{
	return m_squares;
}

std::string game::Map::ToString() const {
	std::string mapString;
	for (size_t y = 0; y < m_height; ++y)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			const auto& square = m_squares.at(y * m_width + x);
			const Tile& tile = square.first;
			const std::shared_ptr<Entity>& entity = square.second;

			if (entity != nullptr && dynamic_cast<Player*>(entity.get())) {
				mapString += "P";
			}
			else {
				switch (tile.GetType()) {
				case Tile::TileType::Free:
					mapString += "F";
					break;
				case Tile::TileType::DestructibleWall:
					mapString += "D";
					break;
				case Tile::TileType::IndestructibleWall:
					mapString += "I";
					break;
				}
			}
		}
		mapString += "\n";
	}
	return mapString;
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
	if (x >= m_width || y >= m_height || x < 0 || y < 0)
		throw std::out_of_range{ "Attempting to access Tile outside defined bounds!" };
	return m_squares.at(y * m_width + x).first;
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

void game::Map::PlacePlayer()
{
	std::array<Map::Position, 4> corners =
	{
		std::make_pair(0, 0),
		{m_width - 1, 0},
		{0, m_height - 1},
		{m_width - 1, m_height - 1}
	};

	//TODO: Think of a way to shuffle players in the array (std::shuffle didn't work)
	//Reason: Player placement is influenced by order of joining the game

	for (int i = 0; i < 4; ++i)
	{
		auto& [x, y] = corners[i];
		m_squares.at(y * m_width + x).second = m_players[i];
	}

	std::cout << "Players placed in corners of the map." << std::endl;
}

void game::Map::MovePlayer(uint32_t playerID, Direction direction)
{
	for (auto& player : m_players)
	{
		if (player->GetID() == playerID)
		{
			auto& playerPos = player->GetPosition();
			size_t newCol = playerPos.first;
			size_t newRow = playerPos.second;

			switch (direction)
			{
			case Direction::UP:
				newRow -= 1;
				break;
			case Direction::DOWN:
				newRow += 1;
				break;
			case Direction::LEFT:
				newCol -= 1;
				break;
			case Direction::RIGHT:
				newCol += 1;
				break;
			}

			if (newRow >= 0 && newRow < m_height && newCol >= 0 && newCol < m_width)
			{
				if (m_squares.at(newRow * m_width + newCol).second == nullptr
					&& m_squares.at(newRow * m_width + newCol).first.GetType() == Tile::TileType::Free)
				{
					m_squares.at(newRow * m_width + newCol).second = std::move(m_squares.at(playerPos.first * m_width + playerPos.second).second);
					player->SetPosition({ newRow, newCol });
				}
			}
			break;
		}
	}
}

void game::Map::InsertPlayer(const std::shared_ptr<Player>& playerPtr)
{
	for (auto& player : m_players)
	{
		if (!player)
		{
			player = playerPtr;
			break;
		}
	}
}




#include "Map.h"
#include <vector>
#include "PowerUp.h"

using namespace game;

namespace ranges = std::ranges;
namespace views = std::views;


const Map::Square& Map::operator[](const Position& pos) const
{
	const auto& [x, y] = pos;
	if (x >= m_width || y >= m_height || x < 0 || y < 0)
	{
		throw std::out_of_range("Invalid position accessed");
	}
	return m_squares.at(y * m_width + x);
}

Map::Square& Map::operator[](const Position& pos)
{
	return const_cast<Map::Square&>(std::as_const(*this)[pos]);
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
		{
			type = Tile::TileType::Free;
		}
		else if (random >= 50 && random <= 85)
		{
			type = Tile::TileType::DestructibleWall;
		}
		else
		{
			type = Tile::TileType::IndestructibleWall;
		}

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

std::string game::Map::GetTileLayout() const
{
	std::string result{};

	for (const auto& elem : m_squares)
	{
		result.push_back(static_cast<int>(elem.first.GetType()));
		result.push_back(' ');
	}

	return result;
}

std::string game::Map::GetEntityLayout() const
{
	std::string result{};

	for (const auto& elem : m_squares)
	{
		if (auto player = std::dynamic_pointer_cast<Player>(elem.second); player)
		{
			result += std::to_string(player->GetID());
		}
		else if (auto bomb = std::dynamic_pointer_cast<Bomb>(elem.second); bomb)
		{
			result += "B";
		}
		else if (auto powerUp = std::dynamic_pointer_cast<PowerUp>(elem.second); powerUp)
		{
			result += "P";
		}
		else if (auto bullet = std::dynamic_pointer_cast<Bullet>(elem.second); bullet)
		{
			result += "b";
		}
		else
		{
			result += "N";
		}
		result.push_back(' ');
	}

	return result;
}

size_t Map::GetWidth() const
{
	return m_width;
}

size_t Map::GetHeight() const
{
	return m_height;
}

Tile Map::GetTile(const Position& pos) const
{
	if (pos.first >= m_width || pos.second >= m_height || pos.first < 0 || pos.second < 0)
		throw std::out_of_range{ "Attempting to access Tile outside defined bounds!" };
	return m_squares.at(pos.second * m_width + pos.first).first;
}

void Map::PlaceBombsOnWalls(std::vector<Bomb>& bombs)
{

	std::vector<Position> destructibleWalls;
	for (size_t y = 0; y < m_height; ++y)
	{
		for (size_t x = 0; x < m_width; ++x)
		{
			const Tile& tile = GetTile({x, y});
			if (tile.GetType() == Tile::TileType::DestructibleWall)
			{
				destructibleWalls.emplace_back(x, y);
			}
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(destructibleWalls.begin(), destructibleWalls.end(), gen);

	for (size_t i = 0; i < std::min(kNoBombs, destructibleWalls.size()); ++i)
	{
		auto [x, y] = destructibleWalls[i];
		(*this)[{x, y}].second = std::make_shared<Bomb>(Position{x, y});
	}
}

void Map::PlacePlayers()
{
	std::array<Map::Position, 4> corners =
	{
		Position{0, 0},
		Position{m_width - 1, 0},
		Position{0, m_height - 1},
		Position{m_width - 1, m_height - 1}
	};

	//TODO: Think of a way to shuffle players in the array

	for (int i = 0; i < 4; ++i)
	{
		auto& [x, y] = corners[i];
		(*this)[{x, y}].second = m_players[i];
	}

	std::cout << "Players placed in corners of the map." << std::endl;
}

void Map::MovePlayer(uint32_t playerID, Direction direction)
{

	auto matchID = [playerID](const std::shared_ptr<Player>& player) -> bool
		{
			if (player->GetID() == playerID)
				return true;
		};

	auto player = ranges::find_if(m_players, matchID);

	if ((*player)->GetID() == playerID)
	{
		const auto& playerPos = (*player)->GetPosition();
		auto newPos = GetPositionAfterDirection(playerPos, direction);

		if (const auto& [newCol, newRow] = newPos;
			newRow >= 0 && newRow < m_height && newCol >= 0 && newCol < m_width)
		{
			if ((*this)[{newCol, newRow}].second == nullptr
				&& (*this)[{newCol, newRow}].first.GetType() == Tile::TileType::Free)
			{
				(*this)[{newCol, newRow}].second = std::move((*this)[{playerPos.first, playerPos.second}].second);
				(*player)->SetPosition({ newCol, newRow });
			}
		}
	}

}

void Map::InsertPlayer(const std::shared_ptr<Player>& playerPtr)
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

void Map::ShootBullet(uint32_t playerID)
{
	auto matchID = [playerID](const std::shared_ptr<Player>& player) -> bool
		{
			if (player->GetID() == playerID)
				return true;
			return false;
		};

	auto playerPtr = ranges::find_if(m_players, matchID);

	if (playerPtr == m_players.end())
	{
		throw std::exception{ "Player not found" };
	}

	auto direction = (*playerPtr)->GetDirection();

	if (auto bulletPos = GetPositionAfterDirection((*playerPtr)->GetPosition(), direction);  
		bulletPos.first >= 0 && bulletPos.second >= 0 && bulletPos.first < m_width && bulletPos.second < m_height)
	{
		if ((*this).GetTile({bulletPos.first, bulletPos.second}).GetType() == Tile::TileType::Free)
		{
			(*this)[{bulletPos.first, bulletPos.second}].second = std::make_shared<Bullet>(*((*playerPtr).get()));
		}
	}
}

std::ostream& game::operator<<(std::ostream& out, const Map& map)
{
	out << "Map Dimensions: " << map.GetWidth() << " x " << map.GetHeight() << "\n";

	for (size_t y = 0; y < map.GetHeight(); ++y)
	{
		for (size_t x = 0; x < map.GetWidth(); ++x)
		{
			const auto& square = map[{x, y}];

			if (const std::shared_ptr<Entity>& entity = square.second; entity != nullptr && std::dynamic_pointer_cast<Player>(entity))
			{
				out << "P" << " ";
			}
			else if (std::dynamic_pointer_cast<Bullet>(entity))
			{
				out << "B" << " ";
			}
			else {
				switch (const Tile& tile = square.first; tile.GetType()) {
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

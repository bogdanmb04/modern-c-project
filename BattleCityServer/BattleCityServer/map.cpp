#include "Map.h"
#include <vector>
#include <queue>
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


Map::Map()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<size_t> widthDist(kWidthMin, kWidthMax);
	std::uniform_int_distribution<size_t> heightDist(kHeightMin, kHeightMax);

	m_width = widthDist(gen);
	m_height = heightDist(gen);

	m_squares.reserve(m_width * m_height);

	for (size_t index = 0; index < m_height * m_width; ++index)
	{
		//instead of equal chance for all tiles, 50% free, 45% destructible wall, 5% indestructible
		Tile::TileType type;
		std::uint8_t random = gen() % 100;
		if (random < 50)
		{
			type = Tile::TileType::Free;
		}
		else if (random >= 50 && random <= 95)
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

}

void Map::MovePlayer(uint32_t playerID, Direction direction)
{
	auto matchID = [playerID](const std::shared_ptr<Player>& player) -> bool
		{
			return player->GetID() == playerID;
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

void Map::KillPlayer(uint32_t playerID)
{
	auto player = ranges::find_if(m_players, [playerID](std::shared_ptr<Player> playerPtr) -> bool
		{
		return playerPtr.get()->GetID() == playerID;
		});
	(*player).get()->DecreaseLives();
	Position playerInitialPosition = (*player).get()->GetStartingPosition();
	(*this)[playerInitialPosition].second = std::move((*this)[(*player).get()->GetPosition()].second);
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
	
	auto& weapon = const_cast<Weapon&>((*playerPtr)->GetWeapon());

	if (weapon.GetTimer().GetElapsedTime() < weapon.GetBulletWaitTime())
	{
		return;
	}

	auto direction = (*playerPtr)->GetDirection();

	if (auto bulletPos = GetPositionAfterDirection((*playerPtr)->GetPosition(), direction);  
		bulletPos.first >= 0 && bulletPos.second >= 0 && bulletPos.first < m_width && bulletPos.second < m_height)
	{
		auto spawnTileType = (*this).GetTile(bulletPos).GetType();

		if (spawnTileType == Tile::TileType::Free && (*this)[bulletPos].second == nullptr)
		{
			(*this)[bulletPos].second = std::make_shared<Bullet>(*((*playerPtr).get()));
		}
		else if (auto playerPtr = std::dynamic_pointer_cast<Player>((*this)[bulletPos].second); playerPtr)
		{
			(*this).KillPlayer(playerPtr.get()->GetID());
		}
		else if (spawnTileType == Tile::TileType::DestructibleWall)
		{
			(*this)[bulletPos].first.SetType(Tile::TileType::Free);
		}
	}
}

void Map::ExplodeBomb(const Position& bomb)
{

}

void Map::MoveBullet(const Position& posBullet)
{
	auto&& bullet = std::move(std::dynamic_pointer_cast<Bullet>((*this)[posBullet].second));

	if (!bullet)
	{
		return;
	}

	if (bullet.get()->GetSpeedBuildUp() < Bullet::kMinimumSpeedBuildup) //cannot move yet
	{
		return;
	}

	(*this)[posBullet].second.reset();

	auto bulletPos = GetPositionAfterDirection(bullet.get()->GetPosition(), bullet.get()->GetDirection());

	if (bulletPos.first >= m_width || bulletPos.second >= m_height)
	{
		bullet.reset();
		return;
	}
	
	auto& nextSquare = (*this)[bulletPos];

	if (nextSquare.first.GetType() == Tile::TileType::DestructibleWall)
	{
		bullet.reset();
		nextSquare.first.SetType(Tile::TileType::Free);
		if (auto bombPtr = std::dynamic_pointer_cast<Bomb>(nextSquare.second); bombPtr)
		{
			(*this).ExplodeBomb(bombPtr.get()->GetPosition()); //IMPLEMENT THIS!!
		}
		return;
	}

	if (nextSquare.first.GetType() == Tile::TileType::IndestructibleWall)
	{
		bullet.reset();
		return;
	}

	if (auto playerPtr = std::dynamic_pointer_cast<Player>(nextSquare.second); playerPtr)
	{
		(*this).KillPlayer(playerPtr.get()->GetID());
		bullet.reset();
		return;
	}

	if (auto bulletPtr = std::dynamic_pointer_cast<Bullet>(nextSquare.second); bulletPtr)
	{
		bullet.reset();
		bulletPtr.reset();
		return;
	}

	if (auto bombPtr = std::dynamic_pointer_cast<Bomb>(nextSquare.second); bombPtr)
	{
		bullet.reset();
		return;
	}

	if (nextSquare.first.GetType() == Tile::TileType::Free)
	{
		bullet.get()->ResetSpeedBuildUp();
		bullet.get()->SetPosition(GetPositionAfterDirection(bullet.get()->GetPosition(), bullet.get()->GetDirection()));
		(*this)[bulletPos].second = std::move(bullet);
	}
}

void Map::MoveBullets()
{
	auto view{
		m_squares | views::filter([](const Map::Square& param) -> bool
			{
				if (auto bulletPtr = std::dynamic_pointer_cast<Bullet>(param.second); bulletPtr)
				{
					if (bulletPtr.get()->GetTimer().GetElapsedTime() >= 1.0)
					{
						bulletPtr.get()->AddSpeedBuildUp();
						return true;
					}
				}
				return false;
			})
	};

	for (auto& square : view)
	{
		MoveBullet(square.second.get()->GetPosition());
	}
}
//
//std::vector<Map::Position> Map::FindPath(const Position& start, const Position& goal) {
//	struct Node {
//		Position pos;
//		size_t g_cost;
//		size_t h_cost;
//		size_t f_cost() const { return g_cost + h_cost; }
//
//		bool operator>(const Node& other) const {
//			return f_cost() > other.f_cost();
//		}
//	};
//
//	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_list;
//	std::map<Position, size_t> g_costs;  // Replaced unordered_map with map
//	std::map<Position, Position> came_from; // Replaced unordered_map with map
//
//	open_list.push(Node{ start, 0, CalculateHeuristic(start, goal) });
//	g_costs[start] = 0;
//
//	const std::vector<Position> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
//
//	while (!open_list.empty()) {
//		Node current = open_list.top();
//		open_list.pop();
//
//		if (current.pos == goal) {
//			return ReconstructPath(came_from, current.pos);
//		}
//
//		for (const auto& direction : directions) {
//			Position neighbor = { current.pos.first + direction.first, current.pos.second + direction.second };
//
//			if (isValid(neighbor) && GetTile(neighbor).GetType() != Tile::TileType::IndestructibleWall) {
//				size_t tentative_g_cost = current.g_cost + 1;
//
//				if (g_costs.find(neighbor) == g_costs.end() || tentative_g_cost < g_costs[neighbor]) {
//					g_costs[neighbor] = tentative_g_cost;
//					size_t h_cost = CalculateHeuristic(neighbor, goal);
//					open_list.push(Node{ neighbor, tentative_g_cost, h_cost });
//					came_from[neighbor] = current.pos;
//				}
//			}
//		}
//	}
//
//	return {};
//}
//
//std::vector<Map::Position> Map::ReconstructPath(const std::map<Position, Position>& origin, Position current) {
//	std::vector<Position> path;
//	while (origin.find(current) != origin.end()) {
//		path.push_back(current);
//		current = origin.at(current);
//	}
//
//	std::reverse(path.begin(), path.end());
//	return path;
//}
//
//size_t Map::CalculateHeuristic(const Position& start, const Position& goal) const {
//	size_t dx = std::abs(static_cast<int>(start.first) - static_cast<int>(goal.first));
//	size_t dy = std::abs(static_cast<int>(start.second) - static_cast<int>(goal.second));
//	return dx + dy;
//}


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

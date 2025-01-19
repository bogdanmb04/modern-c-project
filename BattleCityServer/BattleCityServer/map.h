#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <random>
#include <array>
#include "Tile.h"
#include "Entity.h"
#include "Bullet.h"
#include <memory>
#include "Player.h"
#include <algorithm>
#include <chrono>
#include <ranges>

using std::uint32_t;

namespace game
{
	class Player;

	class Map
	{
	public:
		static const size_t kWidthMin{ 45 };
		static const size_t kWidthMax{ 50 };
		static const size_t kHeightMin{ 25 };
		static const size_t kHeightMax{ 30 };
		static const size_t kNoBombs{ 3 };
		using Position = std::pair<size_t, size_t>;
		using Square = std::pair<Tile, std::shared_ptr<Entity>>;

	public:
		Map();
		const std::vector<Square>& GetSquares() const;
		std::string GetTileLayout() const;
		std::string GetEntityLayout() const;

		const Square& operator [] (const Position& pos) const;
		Square& operator [] (const Position& pos);

		size_t GetWidth() const;
		size_t GetHeight() const;
		Tile GetTile(const Position& pos) const;

		void PlaceBombsOnWalls(std::vector<Bomb>& bombs);

		void PlacePlayers();
		void MovePlayer(uint32_t playerID, Direction direction);
		void InsertPlayer(const std::shared_ptr<Player>& player);
		void KillPlayer(uint32_t playerID);
		void ShootBullet(uint32_t playerID);
		void MoveBullets();
		void ExplodeBomb(const Position& bomb);

		//std::vector<Position> FindPath(const Position& start, const Position& goal);
		//bool isValid(const Position& pos) const;
		//std::vector<Position> ReconstructPath(const std::map<Position, Position>& came_from, Position current);
		//size_t CalculateHeuristic(const Position& start, const Position& goal) const;
		
	private:
		void MoveBullet(const Position& bullet);

	private:
		size_t m_width;
		size_t m_height;
		std::vector<Square> m_squares;
		std::array<std::shared_ptr<Player>, 4> m_players;
	};

	std::ostream& operator << (std::ostream& out, const Map& map);
}


  
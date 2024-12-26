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
	class Map
	{
	public:
		static const size_t kWidthMin{ 9 };
		static const size_t kWidthMax{ 12 };
		static const size_t kHeightMin{ 9 };
		static const size_t kHeightMax{ 12 };
		static const size_t kNoBombs{ 3 };
		using Position = std::pair<size_t, size_t>;
		using Square = std::pair<Tile, std::shared_ptr<Entity>>;

	public:
		Map();
		const std::vector<Square>& GetSquares() const;
		std::string ToString() const;
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

		void ShootBullet(uint32_t playerID);

	private:
		size_t m_width;
		size_t m_height;
		std::vector<Square> m_squares;
		std::array<std::shared_ptr<Player>, 4> m_players;
	};

	std::ostream& operator << (std::ostream& out, const Map& map);
}
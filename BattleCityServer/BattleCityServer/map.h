#pragma once
#include <iostream>
import <vector>;
import <optional>;
import <random>;
import "tile.h";
import "entity.h";
import <memory>;
import "player.h";

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
		using Square = std::pair<Tile, std::unique_ptr<Entity>>;

	public:
		Map();

		const std::vector<std::vector<Map::Square>>& GetSquares() const
		{
			return m_squares;
		}

		size_t GetWidth() const;
		size_t GetHeight() const;
		Tile GetTile(size_t x, size_t y) const;
		void PlaceBombsOnWalls(std::vector<Bomb>& bombs);
		void PlacePlayer();
		void MovePlayer(Player& player, char direction);
	private:
		size_t m_width;
		size_t m_height;
		std::vector<std::vector<Square>> m_squares;
	};

	std::ostream& operator << (std::ostream& out, const Map& map);
}
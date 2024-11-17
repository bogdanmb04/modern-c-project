export module map;
import <vector>;
import <optional>;
import <iostream>;
import <random>;

export import tile;
export import bomb;

namespace game
{
	export class Map 
	{
	public:
		static const size_t kWidthMin{ 10 };
		static const size_t kWidthMax{ 50 };
		static const size_t kHeightMin{ 10 };
		static const size_t kHeightMax{ 50 };
		using Position = std::pair<size_t, size_t>;

	public:
		Map();

		size_t GetWidth() const;
		size_t GetHeight() const;
		const Tile& GetTile(size_t x, size_t y);
		void PlaceBombsOnWalls(std::vector<Bomb>& bombs);

		void placePlayer();

	private:
		size_t m_width;
		size_t m_height;
		std::vector<Tile> m_tiles;
	};

	export std::ostream& operator<<(std::ostream& out, Map map);
}
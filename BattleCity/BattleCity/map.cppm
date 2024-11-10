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
		static const size_t kWidthMin{ 50 };
		static const size_t kWidthMax{ 200 };
		static const size_t kHeightMin{ 50 };
		static const size_t kHeightMax{ 200 };
		using Position = std::pair<size_t, size_t>;

	public:
		Map()
		{
			std::random_device rd;
			std::mt19937 gen(rd());

			std::uniform_int_distribution<size_t> widthDist(kWidthMin, kWidthMax);
			std::uniform_int_distribution<size_t> heightDist(kHeightMin, kHeightMax);

			m_width = widthDist(gen);
			m_height = heightDist(gen);

			m_tiles.reserve(m_width * m_height);

			//TODO: add conditions for tiles: how many, where and which type

			for (size_t y = 0; y < m_height; ++y) {
				for (size_t x = 0; x < m_width; ++x) {
					Tile::TileType type = static_cast<Tile::TileType>(gen() % 3);
					m_tiles.emplace_back(type);
				}
			}
		}

		size_t GetWidth() {
			return m_width;
		}

		size_t GetHeight() {
			return m_height;
		} 

		Tile& GetTile(size_t x, size_t y) {
			if (x >= m_width || y >= m_height || x < 0 || y < 0) {
				throw std::out_of_range("Tile coordinates are out of bounds");
			}
			return m_tiles[y * m_width + x];
		}

		void PlaceBombsOnWalls(std::vector<Bomb>& bombs) {
			for (size_t y = 0; y < m_height; ++y) {
				for (size_t x = 0; x < m_width; ++x) {
					Tile& tile = GetTile(x, y);
					if (tile.GetType() == Tile::TileType::DestructibleWall) {
						//bombs.emplace_back(x, y);
						std::cout << "Placed bomb at (" << x << ", " << y << ")" << std::endl;
					}
				}
			}
		}

	private:
		size_t m_width;
		size_t m_height;
		std::vector<Tile> m_tiles;
	};

	export std::ostream& operator<<(std::ostream& out, Map map);
}
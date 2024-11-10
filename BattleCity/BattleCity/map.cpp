module map;

std::ostream& game::operator<<(std::ostream& out, Map map)
{
    // TODO: change implementation -> this is just for verification
    out << "Map Dimensions: " << map.GetWidth() << " x " << map.GetHeight() << "\n";

    for (size_t y = 0; y < map.GetHeight(); ++y) {
        for (size_t x = 0; x < map.GetWidth(); ++x) {
            const Tile& tile = map.GetTile(x, y);
            out << "Tile at (" << x << ", " << y << "): ";

            switch (tile.GetType()) {
            case Tile::TileType::Free:
                out << "Free";
                break;
            case Tile::TileType::DestructibleWall:
                out << "Destructible Wall";
                break;
            case Tile::TileType::IndestructibleWall:
                out << "Indestructible Wall";
                break;
            default:
                out << "Unknown Type";
            }
            out << "\n";
        }
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

    m_tiles.reserve(m_width * m_height);

    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            m_tiles.emplace_back(static_cast<Tile::TileType>(gen() % 3));
        }
    }
}

size_t game::Map::GetWidth() const
{
    return m_width;
}

size_t game::Map::GetHeight() const
{
    return m_height;
}

const Tile& game::Map::GetTile(size_t x, size_t y)
{
    if (x >= m_width || y >= m_height || x < 0 || y < 0) {
        throw std::out_of_range("Tile coordinates are out of bounds");
    }
    return m_tiles[y * m_width + x];
}

void game::Map::PlaceBombsOnWalls(std::vector<Bomb>& bombs)
{
    for (size_t y = 0; y < m_height; ++y)
    {
        for (size_t x = 0; x < m_width; ++x)
        {
            const Tile& tile = GetTile(x, y);
            if (tile.GetType() == Tile::TileType::DestructibleWall)
            {
                //bombs.emplace_back(x, y);
                std::cout << "Placed bomb at (" << x << ", " << y << ")" << std::endl;
            }
        }
    }
}

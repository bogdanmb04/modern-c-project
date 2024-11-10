module map;

/**
* 
std::ostream& game::operator<<(std::ostream& out, game::Map map)
{
	// TODO: change implementation -> this is just for verification
	out << "Map Dimensions: " << map.GetWidth() << " x " << map.GetHeight() << "\n";

    for (size_t y = 0; y < map.GetHeight(); ++y) {
        for (size_t x = 0; x < map.GetWidth(); ++x) {
            const Tile& tile = map.GetTile(x, y);
            out << "Tile at (" << tile.getX() << ", " << tile.getY() << "): ";

            switch (tile.getType()) {
            case TileType::Free:
                out << "Free";
                break;
            case TileType::DestructibleWall:
                out << "Destructible Wall";
                break;
            case TileType::IndestructibleWall:
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
*/
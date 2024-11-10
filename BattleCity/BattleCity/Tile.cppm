export module tile;
import <iostream>;
using std::uint8_t;

export class Tile 
{
public:
    enum class TileType : uint8_t
    {
        Free,
        DestructibleWall,
        IndestructibleWall
    };

    Tile(TileType type);

    TileType GetType() const 
    {
        return m_type;
    }

private:
    TileType m_type : 2;
};
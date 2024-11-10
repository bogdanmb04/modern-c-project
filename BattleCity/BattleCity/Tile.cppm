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

public:
    Tile(TileType type);
    Tile(const Tile&) = delete;
    Tile& operator = (const Tile&) = delete;

    TileType GetType() const;

private:
    TileType m_type : 2;
};
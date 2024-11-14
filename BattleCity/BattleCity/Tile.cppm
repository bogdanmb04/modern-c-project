export module tile;

import bomb;
import <iostream>;
using std::uint8_t;

export class Tile 
{
public:
    friend class Bomb;
    enum class TileType : uint8_t
    {
        Free,
        DestructibleWall,
        IndestructibleWall,
        Player
    };

public:
    Tile(TileType type);
    //Tile(const Tile&) = delete;
    //Tile& operator = (const Tile&) = delete;

    TileType GetType() const;

private:
    TileType m_type : 2;
};
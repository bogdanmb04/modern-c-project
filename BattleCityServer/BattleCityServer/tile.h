#pragma once

#include "bomb.h"
#include "entity.h"
using std::uint8_t;

class Tile
{
public:
    friend class Bomb;
    enum class TileType : uint8_t
    {
        Free,
        DestructibleWall,
        IndestructibleWall
    };

public:
    Tile(TileType type);
    //Tile(const Tile&) = delete;
    //Tile& operator = (const Tile&) = delete;

    TileType GetType() const;
    void SetType(TileType type);

private:
    TileType m_type : 2;
};
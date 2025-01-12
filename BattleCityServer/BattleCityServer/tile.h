#pragma once

#include "Bomb.h"
#include "Entity.h"
using std::uint8_t;

class Tile
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
    //Tile(const Tile&) = delete;
    //Tile& operator = (const Tile&) = delete;

    TileType GetType() const;
    void SetType(TileType type);
    char TileTypeToChar() const;

private:
    TileType m_type : 2;
};
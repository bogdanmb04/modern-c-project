#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
import Bomb;

enum TileType
{
    FREE,
    BREAKABLE_WALL,
    INDESTRUCTIBLE_WALL
};


class Tile
{
public:
    TileType type;
    bool hasBomb;
    int x, y;

    Tile(TileType t, int CoordX, int CoordY) : type(t), hasBomb(false), x(CoordX), y(CoordY) {}

    void becomeFree()
    {
        if (type == BREAKABLE_WALL)
        {
            type = FREE;
            std::cout << "Tile at (" << x << ", " << y << ") has become free!\n";
        }
    }


    void detonate()
    {
        if (hasBomb)
        {
            Bomb bomb(x,y);
            bomb.explode();
            hasBomb = false;
        }
    }
};

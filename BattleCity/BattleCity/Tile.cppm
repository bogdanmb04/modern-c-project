export module Tile;


#include <iostream>
export module Tile;



export enum class TileType {
    Free,
    DestructibleWall,
    IndestructibleWall
};

export class Tile {
private:
    TileType type;
    int x;
    int y;

public:
    Tile(TileType t, int xPos, int yPos)
        : type(t), x(xPos), y(yPos) {}


    TileType getType() const {
        return type;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void display() const {
        std::cout << "Tile at (" << x << ", " << y << ") is "
            << (type == TileType::Free ? "Free" :
                type == TileType::DestructibleWall ? "Destructible Wall" : "Indestructible Wall")
            << std::endl;
    }
};
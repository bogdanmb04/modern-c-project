export module Bomb;

#include <iostream>

export class Bomb {
private:
    int x;
    int y;
    bool active;

public:
    Bomb(int xPos, int yPos)
        : x(xPos), y(yPos), active(false) {}

    void activate() {
        active = true;
        std::cout << "Bomb activated at (" << x << ", " << y << ")" << std::endl;
    }

    bool explode() {
        if (active) {
            active = false;
            std::cout << "Bomb exploded at (" << x << ", " << y << ")!" << std::endl;
            return true;
        }
        return false;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    bool isActive() const {
        return active;
    }
};
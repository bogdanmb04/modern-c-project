class Bomb
{
public:
    struct Position
    {
        int x, y;
    };
    Position position;
    int radius;
    Bomb(Position p, int r) : position(p), radius(r) {}

    void explode()
    {
        std::cout << "Bomb exploded at (" << position.x << "," << position.y << ") with radius" << radius << "!\n";
    }
};

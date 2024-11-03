#include <cmath>
export module Bullet;

export class Bullet {
private:
    float direction;   
    float speed;       
    bool active;      
    float x;         
    float y;          

public:
    Bullet(float dir, float spd, float startX, float startY)
        : direction(dir), speed(spd), active(true), x(startX), y(startY) {}

    void updatePosition(float deltaTime) {
     
        x += speed * deltaTime * cos(direction);
        y += speed * deltaTime * sin(direction);
    }

    void checkCollision();
    void breakWall();
    void killPlayer();
    void cancelBullet();

    float getDirection() const { return direction; }
    float getSpeed() const { return speed; }
    bool isActive() const { return active; }

    float getX() const { return x; }  
    float getY() const { return y; }  

    bool isCollidingWithWall() { return false; }
    bool isCollidingWithPlayer() { return false; }
    bool isCollidingWithIndestructible() { return false; }
};

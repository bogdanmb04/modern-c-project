export module Bullet;

export class Bullet {
private:
    float direction;
    float speed;
    bool active;

public:
    Bullet(float dir, float spd)
        : direction(dir), speed(spd), active(true) {}

   
    void checkCollision();

    
    void breakWall();

   
    void killPlayer();

   
    void cancelBullet();

  
    float getDirection() const { return direction; }
    float getSpeed() const { return speed; }
    bool isActive() const { return active; }

    bool isCollidingWithWall() 
    { 
      return false; 
    }
    bool isCollidingWithPlayer() {
        return false; }
    bool isCollidingWithIndestructible() { 
        return false;
    }

};

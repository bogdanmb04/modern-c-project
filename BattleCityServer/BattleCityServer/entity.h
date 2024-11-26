#pragma once
#include <utility>
#include <cstdlib>

using std::uint16_t;

class Entity 
{
public:
    virtual ~Entity() = default;
    Entity& operator = (Entity&&) noexcept = default;
    Entity(Entity&&) noexcept = default;
    Entity() = default;
    
protected:
    std::pair<uint16_t, uint16_t> position;

    /*virtual void SetInvisible(bool invisible) = 0;
    virtual void InvertControls(bool invert) = 0;
    virtual void ApplyDamage(int amount) = 0;
    virtual void DestroyWalls(int radius) = 0;*/

};

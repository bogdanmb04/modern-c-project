#pragma once
class Entity 
{
public:
    virtual ~Entity() = default;
    Entity& operator = (Entity&&) noexcept = default;
    Entity(Entity&&) noexcept = default;
    Entity() = default;

    /*virtual void SetInvisible(bool invisible) = 0;
    virtual void InvertControls(bool invert) = 0;
    virtual void ApplyDamage(int amount) = 0;
    virtual void DestroyWalls(int radius) = 0;*/

};

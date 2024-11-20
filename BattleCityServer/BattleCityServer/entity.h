#pragma once
class Entity 
{
public:
    virtual ~Entity() = default;
    Entity& operator = (Entity&&) noexcept = default;
    Entity(Entity&&) noexcept = default;
    Entity() = default;
};

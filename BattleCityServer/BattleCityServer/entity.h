#pragma once
#include <utility>
#include <cstdlib>

using std::uint16_t;

class Entity 
{
public:
    virtual ~Entity() = default;
    Entity() = default;
public:
    void SetPosition(const std::pair<size_t, size_t>& position);
    const std::pair<size_t, size_t>& GetPosition() const;
protected:
    std::pair<size_t, size_t> m_position; //x, y

    /*virtual void SetInvisible(bool invisible) = 0;
    virtual void InvertControls(bool invert) = 0;
    virtual void ApplyDamage(int amount) = 0;
    virtual void DestroyWalls(int radius) = 0;*/

};

#include "PowerUp.h"
using namespace game;

PowerUp::PowerUp(PowerUpType type, std::string effect)
    : m_type(type)
    , m_effect(effect) 
{}

PowerUp::PowerUp(const PowerUp& other) 
    : m_type(other.m_type)
    , m_effect(other.m_effect)
{}

PowerUpType PowerUp::GetType() const noexcept 
{ 
    return m_type; 
}

const std::string PowerUp::GetEffect() const noexcept
{
    return m_effect;
}

std::string PowerUp::PowerUpTypeToString(PowerUpType type) const
{
    switch (type) 
    {
    case PowerUpType::GhostBullet: return "Ghost Bullet";
    case PowerUpType::MiniBombBullet: return "Mini Bomb Bullet";
    case PowerUpType::Invisibility: return "Invisibility";
    case PowerUpType::TracingBullet: return "Tracing Bullet";
    case PowerUpType::BeerEffect: return "Beer Effect";
    default: return "Unknown PowerUp";
    }
}

PowerUp* PowerUp::CreateGhostBullet()
{
    return new PowerUp(PowerUpType::GhostBullet, "Makes bullets pass through walls.");
}

PowerUp* PowerUp::CreateMiniBombBullet()
{
    return new PowerUp(PowerUpType::MiniBombBullet, "Makes bullets explode in a small radius on impact");
}

PowerUp* PowerUp::CreateInvisibility()
{
    return new PowerUp(PowerUpType::Invisibility, "Player becomes invisible for 10 seconds");
}

PowerUp* PowerUp::CreateTracingBullet()
{
    return new PowerUp(PowerUpType::TracingBullet, "Avoids obstacles to seek the nearest target.");
}

PowerUp* PowerUp::CreateBeerEffect()
{
    return new PowerUp(PowerUpType::BeerEffect, "Inverts controls for all other players.");
}


void PowerUp::Activate(Entity& target) {
    switch (m_type) {
    case PowerUpType::GhostBullet:
        // interfata + coliziuni

        break;

    case PowerUpType::Invisibility:
        //target.SetInvisible(true);
        break;

    case PowerUpType::BeerEffect:
        //target.InvertControls(true);
        break;

    case PowerUpType::MiniBombBullet:
        /*target.DestroyWalls(m_attribute_value);
        target.ApplyDamage(m_attribute_value);*/
        break;

    case PowerUpType::TracingBullet:
        // target.A*();
        break;

    default:
        break;
    }
}

void PowerUp::Deactivate(Entity& target) {
    switch (m_type) {
    case PowerUpType::Invisibility:
        //target.SetInvisible(false);

        break;

    case PowerUpType::BeerEffect:
        //target.InvertControls(false);
        break;

    default:
        break;
    }
}



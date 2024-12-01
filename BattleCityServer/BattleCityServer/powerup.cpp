#include "powerup.h"
using namespace game;

game::PowerUp::PowerUp(PowerUpType type, int attribute_value, std::string effect)
    : m_type(type), m_attribute_value(attribute_value), m_effect(effect) {}

game::PowerUp::PowerUp(const PowerUp& other) : m_type(other.m_type), m_attribute_value(other.m_attribute_value), m_effect(other.m_effect), m_duration(other.m_duration) {}

game::PowerUp::PowerUp(PowerUp&& other) noexcept : m_type(std::move(other.m_type)), m_attribute_value(std::move(other.m_attribute_value)),
m_effect(std::move(other.m_effect)), m_duration(std::move(other.m_duration)) {}

PowerUpType game::PowerUp::GetType() const noexcept 
{ 
    return m_type; 
}

int game::PowerUp::GetAttributeValue() const noexcept
{
    return m_attribute_value;
}

const std::string game::PowerUp::GetEffect() const noexcept
{
    return m_effect;
}

void game::PowerUp::SetDuration(int seconds)
{
    m_duration = seconds;
}

int game::PowerUp::GetDuration() const noexcept
{
    return m_duration;
}

std::string game::PowerUp::ToString() const
{
    std::string description = "PowerUp: " + PowerUpTypeToString(m_type) + "\n";
    description += "Effect: " + std::string(m_effect) + "\n";
    description += "Attribute Value: " + std::to_string(m_attribute_value) + "\n";
    if (m_duration > 0) {
        description += "Duration: " + std::to_string(m_duration) + " seconds\n";
    }
    return description;
}


std::string game::PowerUp::PowerUpTypeToString(PowerUpType type) const
{
    switch (type) {
    case PowerUpType::GhostBullet: return "Ghost Bullet";
    case PowerUpType::MiniBombBullet: return "Mini Bomb Bullet";
    case PowerUpType::Invisibility: return "Invisibility";
    case PowerUpType::TracingBullet: return "Tracing Bullet";
    case PowerUpType::BeerEffect: return "Beer Effect";
    default: return "Unknown PowerUp";
    }
}



std::unique_ptr<PowerUp> game::PowerUp::CreateGhostBullet()
{
    return std::make_unique<PowerUp>(PowerUpType::GhostBullet, 0, "Passes through walls.");
}

std::unique_ptr<PowerUp> game::PowerUp::CreateMiniBombBullet()
{
    return std::make_unique<PowerUp>(PowerUpType::MiniBombBullet, 5, "Explodes on a small radius impact");
}

std::unique_ptr<PowerUp> game::PowerUp::CreateInvisibility()
{
    return std::make_unique<PowerUp>(PowerUpType::Invisibility, 10, "Player becomes invisible for 10 seconds");
}

std::unique_ptr<PowerUp> game::PowerUp::CreateTracingBullet()
{
    return std::make_unique<PowerUp>(PowerUpType::TracingBullet, 1, "Avoids obstacles.");
}

std::unique_ptr<PowerUp> game::PowerUp::CreateBeerEffect()
{
    return std::make_unique<PowerUp>(PowerUpType::BeerEffect, 3, "Inverts controls.");
}

void game::PowerUp::Activate(Entity& target) {
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

void game::PowerUp::Deactivate(Entity& target) {
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



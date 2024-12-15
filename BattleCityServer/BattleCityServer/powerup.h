#pragma once

#include "Entity.h"
#include <string>
#include <memory>
#include <chrono>
#include <cstdint>

namespace game {

    enum class PowerUpType : uint8_t
    {
        GhostBullet,
        MiniBombBullet,
        Invisibility,
        TracingBullet,
        BeerEffect,
        None
    };

    class PowerUp : public Entity 
    {
    public:
        PowerUp(PowerUpType type, std::string effect);
        PowerUp(const PowerUp& other);

        PowerUpType GetType() const noexcept;
        int GetAttributeValue() const noexcept;
        const std::string GetEffect() const noexcept;
        void SetDuration(int seconds);
        int GetDuration() const noexcept;

        std::string ToString() const;
        std::string PowerUpTypeToString(PowerUpType type) const;

        static PowerUp* CreateGhostBullet();
        static PowerUp* CreateMiniBombBullet();
        static PowerUp* CreateInvisibility();
        static PowerUp* CreateTracingBullet();
        static PowerUp* CreateBeerEffect();

        void Activate(Entity& target);
        void Deactivate(Entity& target);

    public:
        static constexpr std::chrono::seconds kDuration{ 10 };

    private:
        PowerUpType m_type : 3;
        std::string m_effect;
    };

}


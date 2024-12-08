#pragma once

#include "Entity.h"
#include <string>
#include <memory>

namespace game {

    enum class PowerUpType {
        GhostBullet,
        MiniBombBullet,
        Invisibility,
        TracingBullet,
        BeerEffect
    };

    class PowerUp : public Entity {
    public:
        PowerUp(PowerUpType type, int attribute_value, std::string effect);
        PowerUp(const PowerUp& other);
        PowerUp(PowerUp&& other) noexcept;


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

    private:
        PowerUpType m_type;
        int m_attribute_value;
        std::string m_effect;
        int m_duration;
    };

}


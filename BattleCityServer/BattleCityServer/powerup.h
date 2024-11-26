#pragma once

#include "entity.h"
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
        PowerUp(const PowerUp& other)
            : m_type(other.m_type), m_attribute_value(other.m_attribute_value), m_effect(other.m_effect), m_duration(other.m_duration) {}
        PowerUp(PowerUp&& other) noexcept
            : m_type(std::move(other.m_type)), m_attribute_value(std::move(other.m_attribute_value)),
            m_effect(std::move(other.m_effect)), m_duration(std::move(other.m_duration)) {}


        PowerUpType GetType() const noexcept { return m_type; }
        int GetAttributeValue() const noexcept { return m_attribute_value; }
        const std::string GetEffect() const noexcept { return m_effect; }
        void SetDuration(int seconds) { m_duration = seconds; }
        int GetDuration() const noexcept { return m_duration; }

        std::string ToString() const;
        std::string PowerUpTypeToString(PowerUpType type) const;

        static std::unique_ptr<PowerUp> CreateGhostBullet();
        static std::unique_ptr<PowerUp> CreateMiniBombBullet();
        static std::unique_ptr<PowerUp> CreateInvisibility();
        static std::unique_ptr<PowerUp> CreateTracingBullet();
        static std::unique_ptr<PowerUp> CreateBeerEffect();

        void Activate(Entity& target);
        void Deactivate(Entity& target);


    private:
        PowerUpType m_type;
        int m_attribute_value;
        std::string m_effect;
        int m_duration;
    };

}


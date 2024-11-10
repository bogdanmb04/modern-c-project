export module powerup;

#include <string>

namespace game {

    export class PowerUp {
    public:
        PowerUp(const std::string& name, int attribute_value, const std::string& effect)
            : m_name(name), m_attribute_value(attribute_value), m_effect(effect) {}

        const std::string& getName() const { return m_name; }
        int getAttributeValue() const { return m_attribute_value; }
        const std::string& getEffect() const { return m_effect; }

    private:
        std::string m_name;
        int m_attribute_value;
        std::string m_effect;
    };
}

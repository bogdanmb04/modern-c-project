#pragma once

import <string>;

namespace game {

    class PowerUp {
    public:
        PowerUp(const std::string& name, int attribute_value, const std::string& effect);

        const std::string& getName() const { return m_name; }
        int getAttributeValue() const { return m_attribute_value; }
        const std::string& getEffect() const { return m_effect; }

    private:
        std::string m_name;
        int m_attribute_value;
        std::string m_effect;
    };
}

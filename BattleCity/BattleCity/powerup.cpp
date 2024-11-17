module powerup;

game::PowerUp::PowerUp(const std::string& name, int attribute_value, const std::string& effect)
	: m_name(name), m_attribute_value(attribute_value), m_effect(effect) {}
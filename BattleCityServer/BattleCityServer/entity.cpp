#include "entity.h"

void Entity::SetPosition(const std::pair<size_t, size_t>& position)
{
	m_position = position;
}

const std::pair<size_t, size_t>& Entity::GetPosition() const
{
	return m_position;
}

#include "bomb.h"

Bomb::Bomb(const std::pair<uint16_t, uint16_t>& position)
	: m_position{position}
{/*EMPTY*/ }

std::pair<uint16_t, uint16_t> Bomb::GetPosition() const
{
	return m_position;
}

#pragma once

#include "Movable.h"
#include "Entity.h"

using std::uint8_t;
using std::uint16_t;

namespace game
{
	class Bullet : public Entity
	{
	public:
		Bullet(Direction direction, uint16_t speed);
	private:
		Direction m_direction : 2;
		uint16_t m_speed;
	};
}

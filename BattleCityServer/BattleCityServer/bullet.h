#pragma once

#include "Movable.h"
#include "Entity.h"
#include <chrono>

using std::uint8_t;

namespace game
{
	class Bullet : public Entity
	{
	public:
		Bullet(Direction direction, std::chrono::milliseconds speed);
	private:
		Direction m_direction : 2;
		std::chrono::milliseconds m_speed;
	};
}

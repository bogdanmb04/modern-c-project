#pragma once

import "movable.h";
import "entity.h";

using std::uint8_t;
using std::uint16_t;

namespace game
{
	class Bullet : public Entity, IMovable
	{
	public:
		Bullet(Direction direction, uint16_t speed);
		Bullet(Bullet&&) noexcept = default;
		Bullet& operator = (Bullet&&) noexcept = default;
	private:
		Direction m_direction : 2;
		uint16_t m_speed;
	};
}

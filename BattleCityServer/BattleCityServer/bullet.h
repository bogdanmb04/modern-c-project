#pragma once

#include "Movable.h"
#include "Entity.h"
#include "Timer.h"
#include "Player.h"

using std::uint8_t;

namespace game
{
	class Bullet : public Entity
	{
	public:
		Bullet(const Player& player);
		Direction GetDirection() const;

	private:
		Direction m_direction : 2;
		double m_speed;
		Timer m_timer;
	};
}

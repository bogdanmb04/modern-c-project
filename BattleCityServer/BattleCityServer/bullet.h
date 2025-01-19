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

	public:
		Direction GetDirection() const;
		double GetSpeed() const;
		double GetSpeedBuildUp() const;
		std::chrono::steady_clock GetTimeOfLastSpeedUp() const;
		double GetTimeDifference() const;
		void AddSpeedBuildUp();
		void ResetSpeedBuildUp();

	private:
		Direction m_direction : 2;
		const double m_speed;
		double m_speedBuildUp;
		std::chrono::steady_clock m_timeOfLastSpeedUp;
	};
}

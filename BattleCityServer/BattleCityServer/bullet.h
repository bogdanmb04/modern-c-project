#pragma once

#include "Movable.h"
#include "Entity.h"
#include "Timer.h"
#include "Player.h"

using std::uint8_t;


namespace game
{
	class Player;

	class Bullet : public Entity
	{
	public:
		const static int kMinimumSpeedBuildup{ 1 };

	public:
		Bullet(const Player& player);

	public:
		Direction GetDirection() const;
		double GetSpeed() const;
		double GetSpeedBuildUp() const;
		void AddSpeedBuildUp();
		void ResetSpeedBuildUp();
		const Timer& GetTimer() const;

	private:
		Direction m_direction : 2;
		const double m_speed;
		double m_speedBuildUp;
		Timer m_timer;
	};
}

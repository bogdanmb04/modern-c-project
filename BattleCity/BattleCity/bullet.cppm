export module bullet;

import movable;
import <iostream>;
using std::uint8_t;
using std::uint16_t;

namespace game
{
	export class Bullet : public IMovable
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

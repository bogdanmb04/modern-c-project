export module bullet;

import <iostream>;
using std::uint8_t;
using std::uint16_t;

export class Bullet 
{         
public:
	enum class Direction : uint8_t
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

public:
	Bullet(Direction direction, uint16_t speed);
private:
	Direction m_direction : 2;
	uint16_t m_speed;
};

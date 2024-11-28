#pragma once

#include <cstdlib>
using std::uint8_t;

enum class Direction : uint8_t
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class IMovable
{
public:
	virtual ~IMovable() = default;
	virtual void Move() = 0;
};
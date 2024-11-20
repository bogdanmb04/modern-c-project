#pragma once

#include <iostream>

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

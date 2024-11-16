export module movable;

import <iostream>;

export enum class Direction : uint8_t
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

export class IMovable
{
public:
	virtual ~IMovable() = default;
	virtual void Move() = 0;
};
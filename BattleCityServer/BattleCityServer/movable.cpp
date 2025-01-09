#include "movable.h"

std::pair<size_t, size_t> GetPositionAfterDirection(const std::pair<size_t, size_t>& position, Direction direction)
{
	auto [column, line] = position;

	switch (direction)
	{
		case Direction::UP:
		{
			line -= 1;
			break;
		}
		case Direction::DOWN:
		{
			line += 1;
			break;
		}
		case Direction::LEFT:
		{
			column -= 1;
			break;
		}
		case Direction::RIGHT:
		{
			column += 1;
			break;
		}
	}

	return { column, line };
}

Direction StringToDirection(const std::string_view& message)
{
	if (message == "UP")
		return Direction::UP;
	if (message == "DOWN")
		return Direction::DOWN;
	if (message == "LEFT")
		return Direction::LEFT;
	if (message == "RIGHT")
		return Direction::RIGHT;
	throw std::exception{ "Invalid direction" };
}

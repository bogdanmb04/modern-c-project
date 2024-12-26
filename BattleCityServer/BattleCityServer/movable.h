#pragma once

#include <iostream>
#include <utility>
#include <cstdint>

enum class Direction : uint8_t
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

std::pair<size_t, size_t> GetPositionAfterDirection(const std::pair<size_t, size_t>& position, Direction direction);

Direction StringToDirection(const std::string_view& message);
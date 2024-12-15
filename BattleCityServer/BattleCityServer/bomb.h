#pragma once

#include <iostream>

class Bomb
{
public:
	Bomb(const std::pair<size_t, size_t>& position);
	Bomb(Bomb&) = delete;
	Bomb& operator = (Bomb&) = delete;

private:
	std::pair<size_t, size_t> m_position;
};
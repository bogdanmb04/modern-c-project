#pragma once

#include <iostream>
using std::uint16_t;

class Bomb
{
public:
	Bomb(const std::pair<uint16_t, uint16_t>& position);
	Bomb(Bomb&) = delete;
	Bomb& operator = (Bomb&) = delete;

	std::pair<uint16_t, uint16_t> GetPosition() const;

private:
	std::pair<uint16_t, uint16_t> m_position;
};
#pragma once

#include <iostream>
#include "entity.h"

class Bomb : public Entity
{
public:
	Bomb(const std::pair<size_t, size_t>& position);
	Bomb(Bomb&) = delete;
	Bomb& operator = (Bomb&) = delete;
};
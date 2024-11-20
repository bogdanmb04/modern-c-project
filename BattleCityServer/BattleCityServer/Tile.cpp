#include "tile.h"

Tile::Tile(TileType type)
	:m_type{type}
{}

Tile::TileType Tile::GetType() const
{
	return m_type;
}


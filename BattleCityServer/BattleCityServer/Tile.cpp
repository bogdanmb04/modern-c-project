#include "Tile.h"

Tile::Tile(TileType type)
	:m_type{type}
{}

Tile::TileType Tile::GetType() const
{
	return m_type;
}

void Tile::SetType(TileType type)
{
	m_type = type;
}


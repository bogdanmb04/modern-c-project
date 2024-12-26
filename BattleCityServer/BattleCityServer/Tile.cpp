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

char Tile::TileTypeToChar() const
{
	switch (m_type)
	{
	case TileType::Free: return 'F';
	case TileType::DestructibleWall: return 'D';
	case TileType::IndestructibleWall: return 'I';
	}
}


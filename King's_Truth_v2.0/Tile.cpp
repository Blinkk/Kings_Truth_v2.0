#include "Tile.h"

////////////////
// Default tile
////////////////
Tile::Tile()
{
	// Create an empty rect
	sourceRect = { 0, 0, 0, 0 };
}

Tile::~Tile()
{
	// Nothing to deallocate
}

RECT Tile::GetSourceRect()
{
	return sourceRect;
}


////////////////
// Single Tile
////////////////
SingleTile::SingleTile()
{
	// Create a rect
	sourceRect.left = 0;
	sourceRect.right = sourceRect.left + TILE_SIZE_X;
	sourceRect.top = 0;
	sourceRect.bottom = sourceRect.top + TILE_SIZE_Y;
}


////////////////
// Path Tile
////////////////
PathTile::PathTile()
{
	// Create a rect
	sourceRect.left = 32;
	sourceRect.right = sourceRect.left + TILE_SIZE_X;
	sourceRect.top = 128;
	sourceRect.bottom = sourceRect.top + TILE_SIZE_Y;
}
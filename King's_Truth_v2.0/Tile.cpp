#include "Tile.h"

////////////////
// Default tile
////////////////
Tile::Tile()
{

}

void Tile::Render()
{
	Renderer.Render();
}

Tile::~Tile()
{
	// Nothing to deallocate
}


////////////////
// Single Tile
////////////////
SingleWallTile::SingleWallTile(float posX, float posY, std::string textureToUse)
{
	// Initialize Renderer
	Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 1, 0, 0, 0, 0, 0.0f, posX, posY, textureToUse);

	isCollidable = true;
}


////////////////
// Path Tile
////////////////
SinglePathTile::SinglePathTile(float posX, float posY, std::string textureToUse)
{
	// Initialize Renderer
	Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 33, 33, 0, 0, 0.0f, posX, posY, textureToUse);

	isCollidable = false;
}
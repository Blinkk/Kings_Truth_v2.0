#include "Tile.h"

////////////////
// Default tile
////////////////
Tile::Tile()
{

}

void Tile::Render()
{
	if (Renderer.HasTexture())
		Renderer.Render();
}

Tile::~Tile()
{
	// Nothing to deallocate
}


////////////////
// Path Tile (0)
////////////////
SinglePathTile::SinglePathTile(float posX, float posY, std::string textureToUse)
{
	// Initialize Renderer
	Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 33, 33, 0, 0, 0.0f, posX, posY, textureToUse);

	isCollidable = false;
}


/////////////////////
// Alt Path Tile (1)
/////////////////////
SinglePathTileAlt::SinglePathTileAlt(float posX, float posY, std::string textureToUse)
{
	// Initialize Renderer
	Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 32, 32, 0, 0, 0.0f, posX, posY, textureToUse);

	isCollidable = false;
}


///////////////////
// Corner Tile (2)
///////////////////
CornerPathTile::CornerPathTile(float posX, float posY, std::string textureToUse)
{
	// Initialize Renderer
	Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 40, 40, 0, 0, 0.0f, posX, posY, textureToUse);

	isCollidable = false;
}


///////////////////
// Single Wall (3)
///////////////////
SingleWallTile::SingleWallTile(float posX, float posY, std::string textureToUse)
{
	// Initialize Renderer
	Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 0, 0, 0, 0, 0.0f, posX, posY, textureToUse);

	isCollidable = true;
}


///////////////////////
// Wide Wall (4, 5, 6)
///////////////////////
WideWallTilePiece::WideWallTilePiece(float posX, float posY, TILEPOS pos, std::string textureToUse)
{
	// Initialize Renderer
	switch (pos)
	{
	case FIRST:
		Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 1, 1, 0, 0, 0.0f, posX, posY, textureToUse);
		break;

	case SECOND:
		Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 2, 2, 0, 0, 0.0f, posX, posY, textureToUse);
		break;

	case LAST:
		Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 3, 3, 0, 0, 0.0f, posX, posY, textureToUse);
		break;
	}

	isCollidable = true;
}


///////////////////////
// Long Wall (7, 8, 9)
///////////////////////
LongWallTilePiece::LongWallTilePiece(float posX, float posY, TILEPOS pos, std::string textureToUse)
{
	// Initialize Renderer
	switch (pos)
	{
	case FIRST:
		Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 8, 8, 0, 0, 0.0f, posX, posY, textureToUse);
		break;

	case SECOND:
		Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 16, 16, 0, 0, 0.0f, posX, posY, textureToUse);
		break;

	case LAST:
		Renderer.Initialize(1.0f, 1.0f, TILE_SIZE_X, TILE_SIZE_Y, 8, 24, 24, 0, 0, 0.0f, posX, posY, textureToUse);
		break;
	}
	
	isCollidable = true;
}
#ifndef TILE_H
#define TILE_H
#include <iostream>
#include "Collider.h"
#include "stdafx.h"
#include "2DRenderManager.h"
#include "IRenderableObject.h"
using namespace Smoke;

// Tile Size
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 16

// Used for tiles that are 3 wide/long
enum TILEPOS{ FIRST = 0, SECOND, LAST };

namespace TileTypes
{
	const char SINGLE_PATH = '0';
	const char SINGLE_PATH_ALT = '1';
	const char SNGLE_PATH_CORNER = '2';
	const char SINGLE_WALL = '3';
	const char WIDE_WALL_1 = '4';
	const char WIDE_WALL_2 = '5';
	const char WIDE_WALL_3 = '6';
	const char LONG_WALL_1 = '7';
	const char LONG_WALL_2 = '8';
	const char LONG_WALL_3 = '9';
};

struct Tile : public IRenderableObject
{
public:
	Tile();
	virtual ~Tile();

	// Overridden Render()
	void Render() override;

	// Each tile has a renderer
	TwoDRenderManager Renderer;

	// Each tile is either collidable or not
	bool isCollidable;
};


//////////////////
// TileType = '0'
//////////////////
struct SinglePathTile : public Tile
{
public:
	SinglePathTile(float posX, float posY, std::string textureToUse);
};


//////////////////
// TileType = '1'
//////////////////
struct SinglePathTileAlt : public Tile
{
public:
	SinglePathTileAlt(float posX, float posY, std::string textureToUse);
};


//////////////////
// TileType = '2'
//////////////////
struct CornerPathTile : public Tile
{
public:
	CornerPathTile(float posX, float posY, std::string textureToUse);
};


//////////////////
// TileType = '3'
//////////////////
struct SingleWallTile : public Tile
{
public:
	SingleWallTile(float posX, float posY, std::string textureToUse);
};



///////////////////////////
// TileType = '4', '5', '6'
///////////////////////////
struct WideWallTilePiece : public Tile
{
public:
	WideWallTilePiece(float posX, float posY, TILEPOS pos, std::string textureToUse);
};


////////////////////////////
// TileType = '7', '8', '9'
////////////////////////////
struct LongWallTilePiece : public Tile
{
public:
	LongWallTilePiece(float posX, float posY, TILEPOS pos, std::string textureToUse);
};

#endif
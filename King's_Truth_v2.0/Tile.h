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

namespace TileTypes
{
	const char SINGLE_PATH = '0';
	const char SINGLE_WALL = '1';
};

class Tile : public IRenderableObject
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


class SingleWallTile : public Tile
{
public:
	SingleWallTile(float posX, float posY, std::string textureToUse);
};


class SinglePathTile : public Tile
{
public:
	SinglePathTile(float posX, float posY, std::string textureToUse);
};

#endif
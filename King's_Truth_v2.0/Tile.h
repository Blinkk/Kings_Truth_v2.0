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

// Tile types
enum Tile_Types
{
	PATH = 0,
	PATH_2 = 1,
	SINGLE_WALL_1 = 2,
	SINGLE_WALL_2 = 3,
	SINGLE_WALL_3 = 4,
	SINGLE_WALL_4 = 5,
	SINGLE_WALL_5 = 6,
	DOUBLE_WALL_1 = 7,
	DOUBLE_WALL_2 = 8,
	DOUBLE_WALL_3 = 9,
	LONG_WALL_X = 10,
	LONG_WALL_Y = 11
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
};


class SingleWallTile : public Tile
{
public:
	SingleWallTile(float posX, float posY, std::string textureToUse);
	Collider hitBox;
};


class SinglePathTile : public Tile
{
public:
	SinglePathTile(float posX, float posY, std::string textureToUse);
};

#endif
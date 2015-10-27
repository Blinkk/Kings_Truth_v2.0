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
#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include <iostream>
#include "stdafx.h"
using namespace Smoke;

// Tile Size
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 16

// Source map size
#define SOURCE_MAP_X 128
#define SOURCE_MAP_Y 128

// Tile types
enum Tile_Types
{
	PATH = 0,
	PATH_2,
	SINGLE_WALL_1,
	SINGLE_WALL_2,
	SINGLE_WALL_3,
	SINGLE_WALL_4,
	SINGLE_WALL_5,
	DOUBLE_WALL_1,
	DOUBLE_WALL_2,
	DOUBLE_WALL_3,
	LONG_WALL_X,
	LONG_WALL_Y
};

namespace MAPS
{
	unsigned int LEVEL_ONE = 10;
}

class TileManager
{
private:
	// Info variable for source images
	D3DXIMAGE_INFO *sourceImageInfo;

	/*
		This surface will hold the source surface for each map.
		Portions will be copied from this surface to the mapSurface
		to create the desired map layout.

		Note: This surface will be loaded from a file in TileMap()
	*/
	LPDIRECT3DSURFACE9 _sourceSurface;

	/*
		This surface will hold the entirety of the tile map and should
		be drawn the screen in the main render function.
		
		Note: It will be loaded within the TileMap() function and only be
		reloaded at the beginning of a new level / screen.
	*/
	LPDIRECT3DSURFACE9 _mapSurface;

	TileManager();

public:
	static TileManager &GetInstance()
	{
		TileManager *pTemp = NULL;

		if (!pTemp)
		{
			pTemp = new TileManager();
		}

		return (*pTemp);
	}

	~TileManager();

	/*
		This function takes in the name of a specific map as a 
		parameter and loads that map into the map surface

		Note: This should only be called at the beginning
		of a new level and never within any updates
	*/
	void TileMap(std::string fileName, unsigned int levelID);

	/*
		This function will simply draw the map to the screen

		Note: This should be called in the main Render()
	*/
	void DrawMap();

};

#endif
#ifndef TILEMANAGER_H
#define TILEMANAGER_H
#include <iostream>
#include "Tile.h"
#include "stdafx.h"
using namespace Smoke;

// Source map size
#define SOURCE_MAP_X 128
#define SOURCE_MAP_Y 128

enum MAPS
{
	LEVEL_ONE_MAP = 0
};

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

	/*
		These variables will keep track of the number of rows
		and columns that the map should have based on the size of
		the game screen and the size of each tile (64x64)
	*/
	unsigned int _rows;
	unsigned int _columns;

	TileManager();

	/*
		These functions are used within the TileMap()
		function and are predefined to create a specific
		tiled map setup. New maps must be created manually,
		and their ID must be added to the MAPS enum.
	*/
	void Level_One();


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

		Note: This should ONLY be called at the beginning
		of a new level and never within any updates
	*/
	void TileMap(unsigned int levelID);

	/*
		This function will simply draw the map to the screen

		Note: This should be called in the main Render()
	*/
	void DrawMap();
};

#endif
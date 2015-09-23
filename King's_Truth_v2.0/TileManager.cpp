#include "TileManager.h"
#include "Engine_Core.h"

TileManager::TileManager()
{
	// Initialize source surface
	g_Engine->GetDevice()->CreateOffscreenPlainSurface(SOURCE_MAP_X, SOURCE_MAP_Y,
		D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, &_sourceSurface, NULL);

	// Initialize map surface to be size of game screen
	g_Engine->GetDevice()->CreateOffscreenPlainSurface(SCREENW, SCREENH,
		D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, &_mapSurface, NULL);
}


TileManager::~TileManager()
{
	// Release surfaces
	if (_sourceSurface)
		_sourceSurface->Release();
	if (_mapSurface)
		_mapSurface->Release();

	// Release any other memory
	if (sourceImageInfo)
	{
		delete sourceImageInfo;
		sourceImageInfo = NULL;
	}
}


///////////////////////
// Map tiling function
///////////////////////
void TileManager::TileMap(std::string mapName)
{
	// Load the image into the _sourceSurface
	D3DXLoadSurfaceFromFile(_sourceSurface, NULL, NULL, mapName.c_str(),
		NULL, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), sourceImageInfo);


	/*
		Now copy parts of _sourceSurface to _mapSurface to create
		a tiled map to display in the game. 

		Note: The layouts for these maps are pre-determined and as 
		it is setup right now a new map must be created manually 
		before it can be used using this method.
	*/
	
}
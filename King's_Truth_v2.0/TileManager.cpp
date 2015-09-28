#include "TileManager.h"
#include "Engine_Core.h"

TileManager::TileManager()
{
	// Initialize source surface
	g_Engine->GetDevice()->CreateOffscreenPlainSurface(SOURCE_MAP_X, SOURCE_MAP_Y,
		D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &_sourceSurface, NULL);

	// Initialize map surface to be size of game screen
	g_Engine->GetDevice()->CreateOffscreenPlainSurface(SCREENW, SCREENH,
		D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &_mapSurface, NULL);

	if (!_sourceSurface)
		debug << "Error creating source surface " << std::endl;
	if (!_mapSurface)
		debug << "Error creating map surface " << std::endl;
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
void TileManager::TileMap(std::string fileName, unsigned int levelID)
{
	// Load the image into the _sourceSurface
	HRESULT result = D3DXLoadSurfaceFromFile(_sourceSurface, NULL, NULL, fileName.c_str(),
		NULL, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), sourceImageInfo);

	if (result != D3D_OK)
	{
		debug << "Error loading map surface in TileMap()" << std::endl;
		return;
	}


	/*
		Now copy parts of _sourceSurface to _mapSurface to create
		a tiled map to display in the game. 

		Note: The layouts for these maps are pre-determined and as 
		it is setup right now a new map must be created manually 
		before it can be used using this method.
	*/
	if (levelID == MAPS::LEVEL_ONE)
	{
		result = g_Engine->GetDevice()->UpdateSurface(_sourceSurface, NULL, _mapSurface, NULL);

		if (result != D3D_OK)
		{
			debug << "Error updating map surface in TileMap()" << std::endl;
			return;
		}
	}
	
}


/////////////////////
// Draw map function
/////////////////////
void TileManager::DrawMap()
{
	// Stretct the _mapSurface onto the back buffer
	if (_mapSurface)
		g_Engine->GetDevice()->StretchRect(_mapSurface, NULL, g_Engine->GetBackBuffer(), NULL, D3DTEXF_NONE);
	else
		debug << "\tMap surface is NULL, cannot be drawn." << std::endl;

}


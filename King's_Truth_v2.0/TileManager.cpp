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
	HRESULT result = D3DXLoadSurfaceFromFile(_sourceSurface, NULL, NULL, mapName.c_str(),
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
	
}


/////////////////////
// Draw map function
/////////////////////
void TileManager::DrawMap()
{
	// Stretct the _mapSurface onto the back buffer
	//g_Engine->GetDevice()->StretchRect(_mapSurface, NULL, g_Engine->GetBackBuffer(), NULL, D3DTEXF_NONE);

	g_Engine->GetDevice()->StretchRect(_sourceSurface, NULL, g_Engine->GetBackBuffer(), NULL, D3DTEXF_NONE);
}


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


	// Initialize other variables
	_rows = SCREENH / TILE_SIZE_Y;
	_columns = SCREENW / TILE_SIZE_X;
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

		Note: This is all done manually right now.
	*/
	if (levelID == MAPS::LEVEL_ONE_MAP)
	{
		// Source rect to pull from _sourceSurface and point to draw on _mapSurface
		RECT sourceRect = { 0, 0, TILE_SIZE_X, TILE_SIZE_Y };
		POINT destPoint = { 0, 0 };

		/*
			Note: This section uses std::unique_ptr to create new
			instances of different tile types in varying parts of the code.

			This ensure that the pointers will be released (deallocated)
			as soon as the pointer goes out of scope.
		*/
		// Tile each row
		for (int r = 0; r < _rows; ++r)
		{
			// Tile each column
			for (int c = 0; c < _columns; ++c)
			{
				// If in first or last row
				if (r == 0 || r == _rows - 1)
				{
					// Set up source rect
					std::unique_ptr<SingleTile> pTempTile(new SingleTile());
					sourceRect = pTempTile->GetSourceRect();

					// Copy from source to map
					result = g_Engine->GetDevice()->UpdateSurface(_sourceSurface, &sourceRect, _mapSurface, &destPoint);
					if (result != D3D_OK)
					{
						debug << "Error updating map surface in TileMap() for Map: " << LEVEL_ONE_MAP <<
							" in row: " << r << " and column: " << c << std::endl;
						return;
					}
				}
				else
				{
					// If in first or last column
					if (c == 0 || c == _columns - 1)
					{
						// Set up source rect
						std::unique_ptr<SingleTile> pTempTile(new SingleTile());
						sourceRect = pTempTile->GetSourceRect();

						// Copy from source to map
						result = g_Engine->GetDevice()->UpdateSurface(_sourceSurface, &sourceRect, _mapSurface, &destPoint);
						if (result != D3D_OK)
						{
							debug << "Error updating map surface in TileMap() for Map: " << LEVEL_ONE_MAP <<
								" in row: " << r << " and column: " << c << std::endl;
							return;
						}
					}
					else
					{
						// Set up source rect
						std::unique_ptr<PathTile> pTempTile(new PathTile());
						sourceRect = pTempTile->GetSourceRect();

						// Copy from source to map
						result = g_Engine->GetDevice()->UpdateSurface(_sourceSurface, &sourceRect, _mapSurface, &destPoint);
						if (result != D3D_OK)
						{
							debug << "Error updating map surface in TileMap() for Map: " << LEVEL_ONE_MAP <<
								" in row: " << r << " and column: " << c << std::endl;
							return;
						}
					}
				}

				// Move to next column
				destPoint.x += TILE_SIZE_X;
			}

			// Reset to first column
			destPoint.x = 0;

			// Move to next row
			destPoint.y += TILE_SIZE_Y;
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


#include "TileManager.h"
#include "Engine_Core.h"

TileManager::TileManager()
{
	sourceImageInfo = NULL;

	_tileVect.clear();

	// Get rows and columns
	_rows = SCREENH / TILE_SIZE_Y;
	_columns = SCREENW / TILE_SIZE_X;
}


//////////////////////////////
// Individual Map functions
//////////////////////////////
void TileManager::Level_One()
{
	if (!_tileVect.empty())
	{
		debug << "\tCould not load tile level because vector not empty" << std::endl;
		return;
	}

	////////////////////
	// Create the map
	////////////////////
	float posX = 0;
	float posY = 0;
	for (int r = 0; r < _rows; ++r)
	{
		for (int c = 0; c < _columns; ++c)
		{
			Tile *pTemp = NULL;
			if (c == 0 || r == 0 || c == _columns - 1 || r == _rows - 1)
				pTemp = new SingleWallTile(posX, posY, "SourceMaps/purple_bricks.png");
			else
				pTemp = new SinglePathTile(posX, posY, "SourceMaps/purple_bricks.png");

			// Push the new tile into the vector
			_tileVect.push_back(pTemp);

			posX += TILE_SIZE_X;
		}
		posY += TILE_SIZE_Y;
		posX = 0;
	}
}

TileManager::~TileManager()
{
	// Delete sourceImageInfo pointer
	if (sourceImageInfo)
	{
		delete sourceImageInfo;
		sourceImageInfo = NULL;
	}

	// Empty the vector of tiles
	if (!_tileVect.empty())
	{
		for (std::vector<Tile*>::iterator i = _tileVect.begin(); i != _tileVect.end();)
		{
			delete (*i);
			i = _tileVect.erase(i);
		}
		_tileVect.clear();
	}
}


///////////////////////
// Map tiling function
///////////////////////
void TileManager::TileMap(unsigned int levelID)
{
	if (levelID == LEVEL_ONE_MAP)
	{
		Level_One();
	}
}


///////////////////////
// Draw map function
///////////////////////
void TileManager::DrawMap()
{
	if (!_tileVect.empty())
	{
		// Render all of the tiles
		IRenderableObject *pTemp = NULL;
		for (std::vector<Tile*>::iterator i = _tileVect.begin(); i != _tileVect.end(); ++i)
		{
			/*
				Attempt to cast each object into an IRenderableObject.
				This will ensure that it is a child of IRenderableObject
				and is therefore capable of calling Render()
			*/
			pTemp = dynamic_cast<IRenderableObject*>((*i));

			if (pTemp)
				pTemp->Render();
		}
	}
}


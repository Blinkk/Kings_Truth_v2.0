#include "TileManager.h"
#include "Engine_Core.h"

TileManager::TileManager()
{
	// Get rows and columns
	_rows = SCREENH / TILE_SIZE_Y;
	_columns = SCREENW / TILE_SIZE_X;
}


//////////////////////////////
// Individual Map functions
//////////////////////////////
void TileManager::Level_One()
{
	// Position variables
	float posX = 0.0f;
	float posY = 0.0f;

	// Stream variables
	std::ifstream inStream;
	char currentChar;

	// Open the layout file
	inStream.open("./bin/MapLayouts/Level_One.txt");

	// Get each char and create a tile
	Tile* pTemp = NULL;
	for (int r = 0; r < _rows; ++r)
	{
		for (int c = 0; c < _columns; ++c)
		{
			inStream >> currentChar;
			switch (currentChar)
			{
			// Single path
			case TileTypes::SINGLE_PATH:
				pTemp = new SinglePathTile(posX, posY, "SourceMaps/purple_bricks.png");
				_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

			// Single wall
			case TileTypes::SINGLE_WALL:
				pTemp = new SingleWallTile(posX, posY, "SourceMaps/purple_bricks.png");
				_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

			default:
				debug << "\tFailed to create a tile for Level_One" << std::endl;
				break;
			}
		}

		// Increment position
		posY += TILE_SIZE_Y;
		posX = 0.0f;
	}

	inStream.close();
}

TileManager::~TileManager()
{
	// Empty the map of maps of tiles
	if (!_tileMap.empty())
	{
		std::map<unsigned int, TileRow>::iterator i;
		std::map<unsigned int, Tile*>::iterator j;
		for (i = _tileMap.begin(); i != _tileMap.end();)
		{
			if (!(*i).second.empty())
			{
				for (j = (*i).second.begin(); j != (*i).second.end();)
				{
					delete (*j).second;
					j = (*i).second.erase(j);
				}
				(*i).second.clear();
			}
			i = _tileMap.erase(i);
		}
		_tileMap.clear();
	}
}


///////////////////////
// Map tiling function
///////////////////////
void TileManager::TileMap(unsigned int levelID)
{
	switch (levelID)
	{
	case LEVEL_ONE_MAP:
		Level_One();
		break;
	default:
		debug << "\tFailed to find a map with ID = " << levelID << std::endl;
		break;
	}
}


///////////////////////
// Draw map function
///////////////////////
void TileManager::DrawMap()
{
	std::map<unsigned int, TileRow>::iterator i;
	std::map<unsigned int, Tile*>::iterator j;
	if (!_tileMap.empty())
	{
		// Render all of the tiles
		IRenderableObject *pTemp = NULL;
		for (i = _tileMap.begin(); i != _tileMap.end(); ++i)
		{
			for (j = (*i).second.begin(); j != (*i).second.end(); ++j)
			{
				/*
					Attempt to cast each object into an IRenderableObject.
					This will ensure that it is a child of IRenderableObject
					and is therefore capable of calling Render()
				*/
				pTemp = dynamic_cast<IRenderableObject*>((*j).second);

				if (pTemp)
					pTemp->Render();
			}
		}
	}
}


void TileManager::UpdatePlayerFlags()
{
	// Get a reference to the player and store position
	Player *pTemp = g_Engine->GetPlayer();
	Vector2 playerPos = pTemp->GetCurrentPos();

	// Determine what tile player is on
	unsigned int currentCol = playerPos.GetX() / TILE_SIZE_X;
	unsigned int currentRow = playerPos.GetY() / TILE_SIZE_Y;

	////////////////////////////////
	// Check the surrounding tiles
	////////////////////////////////
	bool canGoLeft, canGoRight, canGoUp, canGoDown;

	// Check left tile
	if (_tileMap[currentRow][currentCol - 1]->isCollidable)
		canGoLeft = false;
	else
		canGoLeft = true;

	// Check right tile
	if (_tileMap[currentRow][currentCol + 1]->isCollidable)
		canGoRight = false;
	else
		canGoRight = true;

	// Check up tile
	if (_tileMap[currentRow - 1][currentCol]->isCollidable)
		canGoUp = false;
	else
		canGoUp = true;

	// Check down tile
	if (_tileMap[currentRow + 1][currentCol]->isCollidable)
		canGoDown = false;
	else
		canGoDown = true;


	/////////////////////////
	// Set player flags
	/////////////////////////
	pTemp->SetMovementFlags(canGoLeft, canGoRight, canGoUp, canGoDown);
}


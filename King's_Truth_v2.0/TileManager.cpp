#include "TileManager.h"
#include "Engine_Core.h"

TileManager::TileManager()
{
	// Get rows and columns
	_rows = SCREENH / TILE_SIZE_Y;
	_columns = SCREENW / TILE_SIZE_X;
}


TileManager::~TileManager()
{
	// Empty the map of maps of tiles
	if (!_tileMap.empty())
	{
		for (_mIt = _tileMap.begin(); _mIt != _tileMap.end();)
		{
			if (!(*_mIt).second.empty())
			{
				for (_tIt = (*_mIt).second.begin(); _tIt != (*_mIt).second.end();)
				{
					delete (*_tIt).second;
					_tIt = (*_mIt).second.erase(_tIt);
				}
				(*_mIt).second.clear();
			}
			_mIt = _tileMap.erase(_mIt);
		}
		_tileMap.clear();
	}
}


///////////////////////
// Map tiling function
///////////////////////
void TileManager::TileMap(unsigned int levelID)
{
	// Map files
	std::string textureFile = "";
	std::string layoutFile = "";

	// Determine which files to use
	switch (levelID)
	{
	case MAPS::PROTOTYPE_MAP:
		textureFile = "SourceMaps/purple_bricks.png";
		layoutFile = "./Textures/MapLayouts/Prototype_Level.txt";
		break;

	case MAPS::LEVEL_ONE_MAP:
		textureFile = "SourceMaps/hedge_maze.png";
		layoutFile = "./Textures/MapLayouts/Level_One.txt";
		break;

	default:
		debug << "\tFailed to find a map with ID = " << levelID << std::endl;
		break;
	}

	
	// Position variables
	float posX = 0.0f;
	float posY = 0.0f;

	// Stream variables
	std::ifstream inStream;
	char currentChar;

	// Open the layout file
	inStream.open(layoutFile);

	// Get each char and create a tile
	Tile* pTemp = nullptr;
	for (int r = 0; r < _rows; ++r)
	{
		for (int c = 0; c < _columns; ++c)
		{
			inStream >> currentChar;
			switch (currentChar)
			{
				// Single path
			case TileTypes::SINGLE_PATH:
				pTemp = new SinglePathTile(posX, posY, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Alt Single path 
			case TileTypes::SINGLE_PATH_ALT:
				pTemp = new SinglePathTileAlt(posX, posY, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Corner path
			case TileTypes::SNGLE_PATH_CORNER:
				pTemp = new CornerPathTile(posX, posY, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Single wall
			case TileTypes::SINGLE_WALL:
				pTemp = new SingleWallTile(posX, posY, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;


				////////////////
				// Wide Wall 
				////////////////
				// Piece 1
			case TileTypes::WIDE_WALL_1:
				pTemp = new WideWallTilePiece(posX, posY, TILEPOS::FIRST, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Piece 2
			case TileTypes::WIDE_WALL_2:
				pTemp = new WideWallTilePiece(posX, posY, TILEPOS::SECOND, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Piece 3
			case TileTypes::WIDE_WALL_3:
				pTemp = new WideWallTilePiece(posX, posY, TILEPOS::LAST, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				////////////////
				// Long Wall 
				////////////////
				// Piece 1
			case TileTypes::LONG_WALL_1:
				pTemp = new LongWallTilePiece(posX, posY, TILEPOS::FIRST, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Piece 2
			case TileTypes::LONG_WALL_2:
				pTemp = new LongWallTilePiece(posX, posY, TILEPOS::SECOND, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

				// Piece 3
			case TileTypes::LONG_WALL_3:
				pTemp = new LongWallTilePiece(posX, posY, TILEPOS::LAST, textureFile);
				if (_tileMap[r][c] == nullptr)
					_tileMap[r][c] = pTemp;
				posX += TILE_SIZE_X;
				break;

			default:
				posX += TILE_SIZE_X;
				break;
			}
		}

		// Increment position
		posY += TILE_SIZE_Y;
		posX = 0.0f;
	}

	inStream.close();
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
		IRenderableObject *pTemp = nullptr;
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


void TileManager::PurgeMapObjects()
{
	// Empty the map of maps of tiles
	if (!_tileMap.empty())
	{
		for (_mIt = _tileMap.begin(); _mIt != _tileMap.end();)
		{
			if (!(*_mIt).second.empty())
			{
				for (_tIt = (*_mIt).second.begin(); _tIt != (*_mIt).second.end();)
				{
					delete (*_tIt).second;
					_tIt = (*_mIt).second.erase(_tIt);
				}
				(*_mIt).second.clear();
			}
			_mIt = _tileMap.erase(_mIt);
		}
		_tileMap.clear();
	}
}


void TileManager::UpdatePlayerFlags()
{
	if (!_tileMap.empty())
	{
		// Get a reference to the player and store position
		Vector2 playerPos;
		Player *pTemp = g_Engine->GetPlayer();
		if (pTemp)
			playerPos = pTemp->GetCurrentPos();
		else
		{
			debug << "\tFailed to get reference to player in TileManager." << std::endl;
			return;
		}

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
}


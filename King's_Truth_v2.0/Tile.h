#ifndef TILE_H
#define TILE_H
#include "Collider.h"
#include "stdafx.h"

// Tile Size
#define TILE_SIZE_X 16
#define TILE_SIZE_Y 16

// Tile types
enum Tile_Types
{
	PATH = 0,
	PATH_2 = 1,
	SINGLE_WALL_1 = 2,
	SINGLE_WALL_2 = 3,
	SINGLE_WALL_3 = 4,
	SINGLE_WALL_4 = 5,
	SINGLE_WALL_5 = 6,
	DOUBLE_WALL_1 = 7,
	DOUBLE_WALL_2 = 8,
	DOUBLE_WALL_3 = 9,
	LONG_WALL_X = 10,
	LONG_WALL_Y = 11
};

class Tile
{
protected:
	RECT sourceRect;

public:
	Tile();
	virtual ~Tile();

	RECT GetSourceRect();
};


class SingleTile : public Tile
{
public:
	SingleTile();
	Collider hitBox;
};


class PathTile : public Tile
{
public:
	PathTile();
};

#endif
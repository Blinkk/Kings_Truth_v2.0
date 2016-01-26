/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Engine_Core.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "StaticBackground.h"
#include "TileManager.h"
#include "Player.h"
#include "Sword.h"
#include "StaticObject.h"
#include "DungeonKey.h"
#include "Chest.h"
#include <Windows.h>
using namespace Smoke;

enum LEVELS
{
	LEVEL_MAIN_MENU = 0,
	LEVEL_ONE = 1,
};

// Typedef std::vector<IGameObject*> for easier syntax
typedef std::vector<IGameObject*> GameObjects;

////////////////////////
// Game Manager class 
////////////////////////
class GameManager : public IGameObject
{
private:
	unsigned int _frameInterval;
	std::map<std::string, GameObjects> _gameObjects;		// Map to hold homogenous vectors of specific object types
	std::map<std::string, GameObjects>::iterator _mIt;		// Map iterator
	std::vector<IGameObject*>::iterator _goIt;				// Sub-vector iterator
	TileManager *_tileManager;								// Tile manager pointer to handle maps
	Camera2D *_camera;										// Camera to control user's viewpoint

	/*
		Keeps track of the currently active level, so that we can go back into
		it if the player dies. Also used to make sure we don't reload the same
		assets unnecessarily.
	*/
	unsigned int _currentLevel;

	/*
		A function pointer that is used to load the necessary assets needed for
		a given level.
	 
		The level functions are defined in GameManager.cpp, and are kept seperate from
		the Game Object so that GameManager doesn't need to have a function for every
		possible level. This allows us to easily add/remove levels without modifying
		too much code.
	*/
	void(*lvlPtr)();

public:
	///////////////////
	// Public variables
	///////////////////
	bool endProgram;
	bool gameOver;

	///////////////////
	// Game functions
	///////////////////
	GameManager();
	virtual ~GameManager();

	bool Game_Init();						// Initialize game specifics
	void Update(float deltaTime) override;	// Main update call
	void Game_Render();						// Render game
	void Game_End();						// Release game objects in level

	void HandleEvent(IEvent* e) override;


	/*
		This function is just a wrapper for levelPointer, and only serves to
		disallow direct access to the function pointer itself.

		This function just calls whatever levelPointer points to.
	*/
	void LoadLevel();


	/*
		This function is used to release all objects
		for a single level to allow for loading of objects
		for a new level. This should be called only from
		the end of the "Level Loop" in Windows.cpp
	*/
	void UnloadLevel();


	//////////////////////
	// Utility functions
	//////////////////////
	void SetGameObjects(std::string key, std::vector<IGameObject*> &levelObjects);
	void PurgeGameObjects();

	//////////////////////////////
	// Accessor/Mutator Functions
	//////////////////////////////
	TileManager* GetTileManager() { return _tileManager; }
	const unsigned int GetFrameInterval() { return _frameInterval; }
	void SetFrameInterval(unsigned int newFrameInterval) { _frameInterval = newFrameInterval; }
	unsigned int GetCurrentLevel() { return _currentLevel; }
};
#endif

extern std::auto_ptr<GameManager> g_Manager;	// Global GameManager object


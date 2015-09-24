/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#pragma once
#include "Engine_Core.h"
#include "Keyboard.h"
#include "TileManager.h"
using namespace Smoke;

////////////////////////////////////////
// Game Manager class 
////////////////////////////////////////
class GameManager : public IGameObject
{
private:
	unsigned int _frameInterval;
	std::vector<IGameObject*>GameObjects;
	std::vector<IGameObject*>::iterator goIt;
	TileManager *_tileManager;

	/*
		Keeps track of the currently active level, so that we can go back into
		it if the player dies. Also used to make sure we don't reload the same
		assets unnecessarily.
	*/
	unsigned int currentLevel;

	/*
		A function pointer that is used to load the necessary assets needed for
		a given level.
	 
		The level functions are defined in Game.cpp, and are kept seperate from
		the Game Object so that Game doesn't need to have a function for every
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
	void Game_End();						// Release game specific memory

	void HandleEvent(IEvent* pEvent) override;


	/*
		This function is just a wrapper for levelPointer, and only serves to
		disallow direct access to the function pointer itself.

		This function just calls whatever levelPointer points to.
	*/
	void LoadLevel();


	//////////////////////
	// Utility functions
	//////////////////////
	void SetGameObjects(std::vector<IGameObject*> levelObjects);
	void PurgeGameObjects();

	//////////////////////////////
	// Accessor/Mutator Functions
	//////////////////////////////
	TileManager* GetTileManager() { return _tileManager; }
	const unsigned int GetFrameInterval() { return _frameInterval; }
	void SetFrameInterval(unsigned int newFrameInterval) { _frameInterval = newFrameInterval; }
};


extern std::auto_ptr<GameManager> g_Manager;	// Global GameManager object


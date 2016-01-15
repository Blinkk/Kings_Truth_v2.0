/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "GameManager.h"


///////////////////////////
// Level load functions
///////////////////////////
void Level1()
{
	// Load all objects for Level1
	std::vector<IGameObject*> gameObjects;

	// Change the camera zoom for this level
	g_Engine->GetActiveCamera()->SetZoomFactor(0.45f);

	//////////////////////////////
	// Create All Game Objects
	//////////////////////////////
	#pragma region ObjectCreation
	// Create player
	Player* pTemp = g_Engine->GetFactory()->CreateObject<Player>();
	if (pTemp)
	{
		gameObjects.push_back(pTemp);

		// Get a global reference to the player
		g_Engine->SetPlayer(pTemp);
	}
		
	else
		debug << "\tFailed to create a 'Player' in Level1 load function" << std::endl;

	//// Create sword
	//Sword* pTemp2 = g_Engine->GetFactory()->CreateObject<Sword>();
	//if (pTemp2)
	//{
	//	pTemp2->Initialize(128, 128);
	//}
	//gameObjects.push_back(pTemp2);

	// Create Key
	DungeonKey *pTemp3 = g_Engine->GetFactory()->CreateObject<DungeonKey>();
	if (pTemp3)
	{
		// Initialize with position / rotation
		float posX = TILE_SIZE_X * 29;
		float posY = TILE_SIZE_Y * 3;
		float rotationInRadians = 0.0f;
		pTemp3->Initialize(posX, posY, rotationInRadians);

		// Add initialized object to vector
		gameObjects.push_back(pTemp3);
	}
	else
		debug << "\tFailed to create a 'DungeonKey' in Level1 load function" << std::endl;

	//////////////////
	// Create chests
	//////////////////
	Chest *pTemp4 = g_Engine->GetFactory()->CreateObject<Chest>();
	if (pTemp4)
	{
		// Initialize with position / rotation
		float posX = TILE_SIZE_X * 48;
		float posY = TILE_SIZE_Y * 35;
		float rotationInRadians = M_PI / 2;
		pTemp4->Initialize(posX, posY, rotationInRadians);

		// Add initialized object to vector
		gameObjects.push_back(pTemp4);
	}
	else
		debug << "\tFailed to create a 'Chest' in Level1 load function" << std::endl;

	///////////////////////
	// Static objects
	///////////////////////
	// Create a barrell
	StaticObject *pTempStatObj = g_Engine->GetFactory()->CreateObject<StaticObject>();
	if (pTempStatObj)
	{
		// Initialize with position / rotation, frame info, etc.
		float posX = TILE_SIZE_X * 42;
		float posY = TILE_SIZE_Y * 34;
		float rotationInRadians = 0.0f;
		pTempStatObj->Initialize(posX, posY, rotationInRadians, 1.0f, 1.0f,
			16, 16, 1, 0, 0, 0, 0, "barrell.png");

		// Add initialized object to vector
		gameObjects.push_back(pTempStatObj);

		// Reset pointer
		pTempStatObj = nullptr;
	}
	else
		debug << "\tFailed to create a 'StaticObject - Barrell' in Level1 load function" << std::endl;

	pTempStatObj = g_Engine->GetFactory()->CreateObject<StaticObject>();
	if (pTempStatObj)
	{
		// Initialize with position / rotation, frame info, etc.
		float posX = TILE_SIZE_X * 46;
		float posY = TILE_SIZE_Y * 34;
		float rotationInRadians = 0.0f;
		pTempStatObj->Initialize(posX, posY, rotationInRadians, 1.0f, 1.0f,
			16, 16, 1, 0, 0, 0, 0, "barrell.png");

		// Add initialized object to vector
		gameObjects.push_back(pTempStatObj);

		// Reset pointer
		pTempStatObj = nullptr;
	}
	else
		debug << "\tFailed to create a 'StaticObject - Barrell' in Level1 load function" << std::endl;
	#pragma endregion
	
	/* 
		THIS IS VERY IMPORTANT FOR LOADING UI OBJECTS 
	*/
	// Update camera position BEFORE loading UI but AFTER player creation
	g_Engine->GetActiveCamera()->UpdatePos();

	//////////////////////////////////
	// Load in the map for this level
	//////////////////////////////////
	g_Manager->GetTileManager()->TileMap(MAPS::LEVEL_ONE_MAP);

	//////////////////////////////////
	// Load in the UI for this level
	//////////////////////////////////
	g_Engine->GetUIManager()->LoadUI(UI_LEVELS::STANDARD_GAMEPLAY_UI);

	//////////////////////////////////////
	// Set the game objects for the level
	//////////////////////////////////////
	g_Manager->SetGameObjects(gameObjects);
}


void Level_MainMenu()
{
	// Load all objects for Level1
	std::vector<IGameObject*> gameObjects;

	// Change the camera zoom for this level
	g_Engine->GetActiveCamera()->SetZoomFactor(1.0f);

	//////////////////////////////////
	// Load the background for level
	//////////////////////////////////
	StaticBackground *background = g_Engine->GetFactory()->CreateObject<StaticBackground>();
	if (background)
		background->Initialize("menu_background.png", SCREENW, SCREENH, Vector2(0, 0));

	g_Engine->GetBackgroundManager()->AddBackground(background);

	//////////////////////////////////
	// Load in the UI for this level
	//////////////////////////////////
	g_Engine->GetUIManager()->LoadUI(UI_LEVELS::MAIN_MENU_UI);

	//////////////////////////////////////
	// Set the game objects for the level
	//////////////////////////////////////
	g_Manager->SetGameObjects(gameObjects);
}


GameManager::GameManager()
{
	endProgram = false;
	gameOver = false;			
	_frameInterval = DEFAULT_FPS;	// Set default fps
	GameObjects.clear();			// Clear vector of GameObjects

	// Set tile manager pointer to nullptr
	_tileManager = nullptr;
	_camera = nullptr;

	lvlPtr = &Level_MainMenu;		// Set default level to Main_Menu
	_currentLevel = LEVELS::LEVEL_MAIN_MENU;	// Set current level
}


GameManager::~GameManager()
{
	// Deallocate memory
	if (_tileManager)
	{
		delete _tileManager;
		_tileManager = nullptr;
	}
}


////////////////////////////////////////
// Initialize game resources
////////////////////////////////////////
bool GameManager::Game_Init()
{
	srand(time(nullptr));

	/////////////////////////
	// Create a camera
	/////////////////////////
	_camera = new Camera2D();
	if (_camera == nullptr)
	{
		debug << "\tFailed to create camera in Game_Init()" << std::endl;
		return false;
	}
	g_Engine->SetActiveCamera(_camera);		// Set global camera pointer

	/////////////////////////
	// Create a tile manager
	/////////////////////////
	_tileManager = &TileManager::GetInstance();
	if (!_tileManager)
	{
		debug << "\tFailed to create tile manager in Game_Init()" << std::endl;
		return false;
	}

	///////////////////////
	// Setup Input devices
	///////////////////////
	Mouse *pMouse = new Mouse();
	if (!pMouse)
	{
		debug << "\tFailed to create a mouse in Game_Init()" << std::endl;
		return false;
	}
	g_Engine->GetInputManager()->SetMouse(pMouse);

	Keyboard *pKeyboard = new Keyboard();
	if (!pKeyboard)
	{
		debug << "\tFailed to create a keyboard in Game_Init()" << std::endl;
		return false;
	}
	g_Engine->GetInputManager()->SetKeyboard(pKeyboard);

	// Key codes
	std::vector<int> codes;
	codes.push_back(DIK_W);			// Move up
	codes.push_back(DIK_A);			// Move left
	codes.push_back(DIK_S);			// Move down
	codes.push_back(DIK_D);			// Move right
	codes.push_back(DIK_SPACE);		// Attack
	codes.push_back(DIK_ESCAPE);	// Open Menu / Exit game
	g_Engine->GetInputManager()->SetDIKKeyboardCodes(codes);

	////////////////////////////
	// Register event listeners
	////////////////////////////
	g_Engine->GetEventManager()->RegisterListener(this, Events::ENDLEVEL);
	g_Engine->GetEventManager()->RegisterListener(this, Events::ENDPROGRAM);

	return true;
}


void GameManager::LoadLevel()
{
	// Call the function that lvlPtr points to
	lvlPtr();

	// Reset the gameOver flag so that the new level can begin
	gameOver = false;
}


void GameManager::UnloadLevel()
{
	// Purge GameObjects
	PurgeGameObjects();

	// Purge UI Objects
	g_Engine->GetUIManager()->PurgeUIObjects();

	// Purge Backgrounds
	g_Engine->GetBackgroundManager()->PurgeBackgrounds();

	// Purge map objects
	_tileManager->PurgeMapObjects();
}


//////////////////////////////////////////////
// Main update function (called in game loop)
//////////////////////////////////////////////
void GameManager::Update(float deltaTime)
{
	/////////////////////////////////
	// Updates various managers
	/////////////////////////////////
	g_Engine->GetInputManager()->Update(deltaTime);
	g_Engine->GetUIManager()->Update(deltaTime);
	g_Engine->GetBackgroundManager()->Update(deltaTime);
	g_Engine->GetDebugger()->Update(deltaTime);

	///////////////////////////////
	// Manage game object updates
	///////////////////////////////
	for (goIt = GameObjects.begin(); goIt != GameObjects.end(); ++goIt)
	{
		(*goIt)->Update(deltaTime);
	}

	// Update player movement flags
	_tileManager->UpdatePlayerFlags();

	// Increment frame count
	g_Engine->IncrementFrameCount();
}


void GameManager::Game_Render()
{
	//////////////////////////////////////////////////////////
	// Clear the backbuffer, render all renderable objects
	// then end the scene and present to game screen
	//////////////////////////////////////////////////////////
	g_Engine->ClearScene();								// Clear the backbuffer for rendering
	if (g_Engine->GetDevice()->BeginScene() == D3D_OK)	// Begin scene
	{
		// Create a projection matrix
		_camera->Render();

		//////////////////////////////
		// Begin Spritebatch for 2D
		g_Engine->GetSpriteObj()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

		// Render backgrounds
		g_Engine->GetBackgroundManager()->Render();

		// Render the map
		_tileManager->DrawMap();

		// Render the renderable game objects
		IRenderableObject *pTemp = nullptr;
		for (goIt = GameObjects.begin(); goIt != GameObjects.end(); ++goIt)
		{
			/*
				Attempt to cast each object into an IRenderableObject.
				This will ensure that it is a child of IRenderableObject
				and is therefore capable of calling Render()
			*/
			pTemp = dynamic_cast<IRenderableObject*>((*goIt));
		
			if (pTemp)
				pTemp->Render();

			// Reset temp pointer
			pTemp = nullptr;
		}

		// Call engine manager render functions
		g_Engine->GetUIManager()->Render();
		g_Engine->GetInputManager()->Render();
		
		// Render debugger as needed
		if (g_Engine->ShowDebug())
			g_Engine->GetDebugger()->Render();

		g_Engine->GetSpriteObj()->End();
		// End Spritebatch for 2D
		//////////////////////////////


		// 3D rendering will go here....

		g_Engine->EndScene();		// End scene and present backbuffer
	}
}


void GameManager::HandleEvent(IEvent *e)
{
	if (e->Event_Type == Events::ENDLEVEL)
	{
		EndLevelEvent *pTemp = static_cast<EndLevelEvent*>(e);
		if (pTemp)
		{
			switch (pTemp->newLevel)
			{
			case LEVELS::LEVEL_MAIN_MENU:
				lvlPtr = &Level_MainMenu;
				break;

			case LEVELS::LEVEL_ONE:
				lvlPtr = &Level1;
				break;

			default:
				debug << "\tFailed to load new level because levelID out of range" << std::endl;
				break;
			}
		}
		gameOver = true;
	}	
	else if (e->Event_Type == Events::ENDPROGRAM)
	{
		// Break out of all game loops and shutdown
		gameOver = true;
		endProgram = true;
	}
		
}


//////////////////////////////////
// Free game specific resources
//////////////////////////////////
void GameManager::Game_End()
{
	// Remove any current game objects
	PurgeGameObjects();
}


//////////////////////
// Utility Functions
//////////////////////
void GameManager::SetGameObjects(std::vector<IGameObject*> levelObjects)
{
	// Deallocate any memory before switching to the new vector
	for (goIt = GameObjects.begin(); goIt != GameObjects.end();)
	{
		delete (*goIt);
		goIt = GameObjects.erase(goIt);
	}

	// Shallow copy the vector to preserve the pointers
	GameObjects = levelObjects;
}


void GameManager::PurgeGameObjects()
{
	// Deallocate any memory before switching to the new vector
	for (goIt = GameObjects.begin(); goIt != GameObjects.end();)
	{
		delete (*goIt);
		goIt = GameObjects.erase(goIt);
	}
}


/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "GameManager.h"
#include "Player.h"


///////////////////////////
// Level load functions
///////////////////////////
void Level1()
{
	// Load all objects for Level1
	std::vector<IGameObject*> gameObjects;

	Player* pTemp = g_Engine->GetFactory()->CreateObject<Player>();
	gameObjects.push_back(pTemp);

	/*
		Not able to find the file...

		TODO: Fix this
	*/
	g_Manager->GetTileManager()->TileMap("./bin/Source Maps/purple_bricks.png");

	// Set the game objects for the level
	g_Manager->SetGameObjects(gameObjects);
}



GameManager::GameManager()
{
	endProgram = false;
	gameOver = false;			
	_frameInterval = DEFAULT_FPS;	// Set default fps
	GameObjects.clear();			// Clear vector of GameObjects

	// Set tile manager pointer to NULL
	_tileManager = NULL;

	lvlPtr = &Level1;				// Set default level to Level1
}


GameManager::~GameManager()
{
	// Deallocate memory
	if (_tileManager)
	{
		delete _tileManager;
		_tileManager = NULL;
	}
}


////////////////////////////////////////
// Initialize game resources
////////////////////////////////////////
bool GameManager::Game_Init()
{
	srand(time(NULL));

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


//////////////////////////////////////////////
// Main update function (called in game loop)
//////////////////////////////////////////////
void GameManager::Update(float deltaTime)
{
	/////////////////////////////////
	// Updates various managers
	/////////////////////////////////
	g_Engine->IncrementFrameCount();
	g_Engine->GetInputManager()->Update(deltaTime);
	g_Engine->GetDebugger()->Update(deltaTime);

	///////////////////////////////
	// Manage game object updates
	///////////////////////////////
	for (goIt = GameObjects.begin(); goIt != GameObjects.end(); ++goIt)
	{
		(*goIt)->Update(deltaTime);
	}
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
		// Render the map
		_tileManager->DrawMap();

		//////////////////////////////
		// Begin Spritebatch for 2D
		g_Engine->GetSpriteObj()->Begin(D3DXSPRITE_ALPHABLEND);

		// Render the renderable game objects
		IRenderableObject *pTemp = NULL;
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


void GameManager::HandleEvent(IEvent *pEvent)
{
	if (pEvent->Event_Type == Events::ENDLEVEL)
		gameOver = true;
	else if (pEvent->Event_Type == Events::ENDPROGRAM)
		endProgram = true;
}


//////////////////////////////////
// Free game specific resources
//////////////////////////////////
void GameManager::Game_End()
{
	// Remove any current game objects
	PurgeGameObjects();

	// Deallocate any other memory here.
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


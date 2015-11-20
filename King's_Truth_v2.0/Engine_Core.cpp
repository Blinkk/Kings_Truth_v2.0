/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

namespace Smoke
{
	Engine_Core::Engine_Core()
	{
		_eventManager = NULL;
		_inputManager = NULL;
		_uiManager = NULL;
		_textureManager = NULL;
		_factory = NULL;
		_debugger = NULL;
		_player = NULL;
		_coreFrameCount = 0;
		_coreTimer = new Timer();

		// Initialize window and Direct3D pointers
		_window = new HWND();
		_d3dDevice = new LPDIRECT3DDEVICE9();
		_d3dContext = new LPDIRECT3D9();
		_backBuffer = new LPDIRECT3DSURFACE9();
		_spriteObj = new LPD3DXSPRITE();
	}


	Engine_Core::~Engine_Core() {}


	bool Engine_Core::Initialize(HINSTANCE hInstance, bool fullScrn)
	{
		debug << "Engine initilization started..." << std::endl;

		_eventManager = &EventManager::GetInstance();			// Create a pointer to event manager
		_inputManager = &InputManager::GetInstance();			// Create a pointer to input manager
		_uiManager = &UIManager::GetInstance();					// Create a pointer to UI manager
		_backgroundManager = &BackgroundManager::GetInstance();	// Create a pointer to Background manager
		_textureManager = &TextureManager::GetInstance();		// Create a pointer to texture manager
		_factory = &Factory::GetInstance();						// Create a pointer to the factory
		_debugger = &Debug::GetInstance();						// Create a pointer to debugger
		_directX = &Direct3D::GetInstance();					// Create a pointer to DirectX wrapper object

		//////////////////////////
		// Initialize DirectX
		//////////////////////////
		if (!_directX->Initialize(hInstance, fullScrn, SCREEN_DEPTH, SCREEN_NEAR))
		{
			debug << "\tFailed to initialize DirectX" << std::endl;
			return false;
		}
		else
			debug << "\tDirectX initialized." << std::endl;

		//////////////////////////////
		// Initialize texture manager
		//////////////////////////////
		if (!_textureManager->Initialize())
		{
			debug << "\tFailed to initialize InputManager" << std::endl;
			return false;
		}
		else
			debug << "\tTexture Manager initialized." << std::endl;

		//////////////////////////
		// Initialize UI object
		//////////////////////////
		//if (!_uiManager->Initialize("Calibri", 24))
		//{
		//	debug << "\tFailed to initialize UI" << std::endl;
		//	return false;
		//}

		/////////////////////////////
		// Initialize input manager
		/////////////////////////////
		if (!_inputManager->Initialize())
		{
			debug << "\tInput failed to initialize." << std::endl;
			return false;
		}
		else
			debug << "\tInput initialized." << std::endl;

		///////////////////////
		// Initialize debugger
		///////////////////////
		if (!_debugger->Initialize())
		{
			debug << "\tFailed to initialize debugger" << std::endl;
			return false;
		}
		else
			debug << "\tDebugger initialized." << std::endl;
		SetShowDebug(true);

		// If everything successful
		debug << "Engine initialized successfully!" << std::endl;
		return true;
	}


	void Engine_Core::Shutdown()
	{
		debug << "Engine shutting down..." << std::endl;

		// Shutdown debugger
		if (_debugger)
		{
			_debugger->Shutdown();
			delete _debugger;
			_debugger = NULL;
		}

		// Delete factory
		if (_factory)
		{
			delete _factory;
			_factory = NULL;
		}

		if (_textureManager)
		{
			_textureManager->Shutdown();
			delete _textureManager;
			_textureManager = NULL;
		}

		// Shutdown UI
		if (_uiManager)
		{
			_uiManager->Shutdown();
			delete _uiManager;
			_uiManager = NULL;
		}
		
		// Shutdown and delete input manager
		if(_inputManager)
		{
			_inputManager->Shutdown();
			delete _inputManager;
			_inputManager = NULL;
		}

		// Shutdown and delete event manager
		if (_eventManager)
		{
			_eventManager->Shutdown();
			delete _eventManager;
			_eventManager = NULL;
		}

		// Shutdown and delete DirectX
		if (_directX)
		{
			_directX->Shutdown();
			delete _directX;
			_directX = NULL;
		}


		////////////////////////////////////////////
		// After all other cores shutdown, delete 
		// memory allocated in main core.
		////////////////////////////////////////////
		if (_backBuffer)
		{
			if ((*_backBuffer)->Release() > 0)
				debug << "\tError releasing D3D backbuffer" << std::endl;

			delete _backBuffer;
			_backBuffer = NULL;
		}

		if (_spriteObj)
		{
			if ((*_spriteObj)->Release() > 0)
				debug << "\tError releasing D3D sprite object" << std::endl;

			delete _spriteObj;
			_spriteObj = NULL;
		}
		if (_d3dContext)
		{
			if ((*_d3dContext)->Release() > 0)
				debug << "\tError releasing D3DContext" << std::endl;

			delete _d3dContext;
			_d3dContext = NULL;
		}
		if (_d3dDevice)
		{
			if ((*_d3dDevice)->Release() > 0)
				debug << "\tError releasing D3DDevice" << std::endl;

			delete _d3dDevice;
			_d3dDevice = NULL;
		}
		
		if (_window)
		{
			delete _window;
		}

		if (_coreTimer)
		{
			delete _coreTimer;
			_coreTimer = NULL;
		}

		debug << "Engine shutdown complete." << std::endl;
	}


	///////////////////////////
	// Utility Functions
	///////////////////////////
	void Engine_Core::ResetFrameCounter()
	{
		_coreFrameCount = 0;
	}


	void Engine_Core::IncrementFrameCount()
	{
		_coreFrameCount++;
	}


	void Engine_Core::ClearScene()
	{
		HRESULT result = GetDevice()->Clear(0, NULL, 
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0);
		if (result != D3D_OK)
		{
			debug << "Failed to clear backbuffer" << std::endl;
		}
	}


	void Engine_Core::EndScene()
	{
		// End scene and present
		GetDevice()->EndScene();
		GetDevice()->Present(NULL, NULL, NULL, NULL);
	}


	/////////////////////////
	// Accessors / Mutators
	/////////////////////////
	// Return a pointer to Event Manager
	EventManager* Engine_Core::GetEventManager()	
	{ 
		if (_eventManager != NULL)
			return _eventManager; 
		else
		{
			debug << "\tFailed to get pointer to EventManager from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}		

	// Return a pointer to Input Manager
	InputManager* Engine_Core::GetInputManager()		
	{ 
		if (_inputManager != NULL)
			return _inputManager;
		else
		{
			debug << "\tFailed to get pointer to InputManager from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}		
	
	// Return a pointer to UI Manager
	UIManager* Engine_Core::GetUIManager() 
	{
		if (_uiManager != NULL)
			return _uiManager; 
		else
		{
			debug << "\tFailed to get pointer to UIManager from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}		

	// Return a pointer to Background Manager
	BackgroundManager* Engine_Core::GetBackgroundManager()
	{
		if (_backgroundManager != NULL)
			return _backgroundManager;
		else
		{
			debug << "\tFailed to get pointer to BackgroundManager from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}
	
	// Return a pointer to texture manager
	TextureManager* Engine_Core::GetTextureManager()	
	{ 
		if (_textureManager != NULL)
			return _textureManager; 
		else
		{
			debug << "\tFailed to get pointer to TextureManager from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}	
	
	// Return a pointer to the camera
	Factory* Engine_Core::GetFactory() 
	{ 
		if (_factory != NULL)
			return _factory; 
		else
		{
			debug << "\tFailed to get pointer to Factory from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}	
	
	// Return a pointer to Debugger
	Debug* Engine_Core::GetDebugger() 
	{
		if (_debugger != NULL)
			return _debugger; 
		else
		{
			debug << "\tFailed to get pointer to Debugger from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}						
	
	// Return a pointer to Core Timer
	Timer* Engine_Core::GetCoreTimer() 
	{
		if (_coreTimer != NULL)
			return _coreTimer; 
		else
		{
			debug << "\tFailed to get pointer to Timer from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}					

	// Return a pointer to the Player
	Player* Engine_Core::GetPlayer()
	{
		if (_player != NULL)
			return _player;
		else
			return NULL;
	}
	
	// Return a pointer to the camera
	Camera2D* Engine_Core::GetActiveCamera() 
	{
		if (_camera != NULL)
			return _camera; 
		else
		{
			debug << "\tFailed to get pointer to Camera from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return NULL;
		}
	}		

	////////////////////////////////////////////////////////

	// Return address of window
	HWND& Engine_Core::GetWindowHandle()
	{ 
		if (_window != NULL)
			return (*_window); 
		else
		{
			debug << "\tFailed to get reference to HWND from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return (*_window);
		}

	}					

	// Return address of d3dDevice
	LPDIRECT3DDEVICE9& Engine_Core::GetDevice() 
	{ 
		if (_d3dDevice != NULL)
			return (*_d3dDevice); 
		else
		{
			debug << "\tFailed to get reference to D3DDEVICE9 from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return (*_d3dDevice);
		}
	}	

	// Return address of d3dContext
	LPDIRECT3D9& Engine_Core::GetContext() 
	{ 
		if (_d3dContext != NULL)
			return (*_d3dContext);
		else
		{
			debug << "\tFailed to get reference to D3DContext9 from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return (*_d3dContext);
		}
	}			

	// Return address of spriteObj
	LPD3DXSPRITE& Engine_Core::GetSpriteObj() 
	{
		if (_spriteObj != NULL)
			return (*_spriteObj); 
		else
		{
			debug << "\tFailed to get reference to D3DXSPRITE from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return (*_spriteObj);
		}
	}			

	// Return address of backbuffer	
	LPDIRECT3DSURFACE9& Engine_Core::GetBackBuffer() 
	{
		if (_backBuffer != NULL)
			return (*_backBuffer); 
		else
		{
			debug << "\tFailed to get reference to BackBuffer from g_Engine at: " << g_Engine->GetGameTime() << std::endl;
			return (*_backBuffer);
		}
	}		

	////////////////////////////////////////////////////////

	// Set the Player pointer
	void Engine_Core::SetPlayer(Player *pPlayer)
	{
		if (pPlayer != NULL)
			_player = pPlayer;
		else
			debug << "\tFailed to set global player pointer in g_Engine at: " << g_Engine->GetGameTime() << std::endl;
	}

	// Set the Camera pointer
	void Engine_Core::SetActiveCamera(Camera2D *pCamera)
	{
		if (pCamera != NULL)
			_camera = pCamera;
		else
			debug << "\tFailed to set global camera pointer in g_Engine at: " << g_Engine->GetGameTime() << std::endl;
	}
}	// End of namespace
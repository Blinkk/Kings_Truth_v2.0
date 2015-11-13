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

		_eventManager = &EventManager::GetInstance();		// Create a pointer to event manager
		_inputManager = &InputManager::GetInstance();		// Create a pointer to input manager
		_uiManager = &UIManager::GetInstance();				// Create a pointer to UI manager
		_textureManager = &TextureManager::GetInstance();	// Create a pointer to texture manager
		_factory = &Factory::GetInstance();					// Create a pointer to the factory
		_debugger = &Debug::GetInstance();					// Create a pointer to debugger
		_directX = &Direct3D::GetInstance();				// Create a pointer to DirectX wrapper object

		//////////////////////////
		// Initialize DirectX
		//////////////////////////
		if (!_directX->Initialize(hInstance, fullScrn, SCREEN_DEPTH, SCREEN_NEAR))
		{
			debug << "\tFailed to initialize DirectX" << std::endl;
			return false;
		}

		//////////////////////////////
		// Initialize texture manager
		//////////////////////////////
		if (!_textureManager->Initialize())
		{
			debug << "\tFailed to initialize InputManager" << std::endl;
			return false;
		}

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
		SetShowDebug(true);

		// If everything successful
		debug << "Engine initialized successfully!" << std::endl;
		return true;
	}


	void Engine_Core::Shutdown()
	{
		int bugs = 0;
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


		////////////////////////////////////////////
		// After all other cores shutdown, delete 
		// memory allocated in main core.
		////////////////////////////////////////////
		if (_backBuffer)
		{
			if ((*_backBuffer)->Release() > 0)
			{
				debug << "\tError releasing D3D backbuffer" << std::endl;
				bugs++;
			}
			delete _backBuffer;
			_backBuffer = NULL;
		}

		if (_spriteObj)
		{
			if ((*_spriteObj)->Release() > 0)
			{
				debug << "\tError releasing D3D sprite object" << std::endl;
				bugs++;
			}
			delete _spriteObj;
			_spriteObj = NULL;
		}
		if (_d3dContext)
		{
			if ((*_d3dContext)->Release() > 0)
			{
				debug << "\tError releasing D3Dcontext" << std::endl;
				bugs++;
			}
			delete _d3dContext;
			_d3dContext = NULL;
		}
		if (_d3dDevice)
		{
			if ((*_d3dDevice)->Release() > 0)
			{
				debug << "\tError releasing D3Ddevice" << std::endl;
				bugs++;
			}
			delete _d3dDevice;
			_d3dDevice = NULL;
		}
		if (_directX)
		{
			_directX->Shutdown();
			delete _directX;
			_directX = NULL;
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

		debug << "Main engine core shutdown with " << bugs << " bugs." << std::endl;
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


	Player* Engine_Core::GetPlayer()
	{
		if (_player != NULL)
			return _player;
		else
			return NULL;
	}


	void Engine_Core::SetPlayer(Player *pPlayer)
	{
		if (pPlayer != NULL)
			_player = pPlayer;
	}
}	// End of namespace
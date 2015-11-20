/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

namespace Smoke
{
	//////////////////////////////
	// Level load Functions - UI
	//////////////////////////////
	void UIManager::Standard_Gameplay_UI()
	{
		std::vector<IUI_Object*> uiObjects;

		//////////////////////////////////////////////////////////////
		// Create UI objects for this setup (STANDARD_GAMEPLAY_UI)
		//
		// Note: This requires that there be an active camera set in
		// the g_Engine global reference.
		//////////////////////////////////////////////////////////////
		Camera2D *pTemp = g_Engine->GetActiveCamera();
		if (pTemp != NULL)
		{
			// Create a test label and initialize it, then add to vector
			
		}

		// Set the UI Objects
		g_Engine->GetUIManager()->SetUIObjects(uiObjects);
	}


	void UIManager::Main_Menu_UI()
	{
		std::vector<IUI_Object*> uiObjects;

		//////////////////////////////////////////////////////////////
		// Create UI objects for this setup (MAIN_MENU_UI)
		//
		// Note: This requires that there be an active camera set in
		// the g_Engine global reference.
		//////////////////////////////////////////////////////////////
		Camera2D *pTemp = g_Engine->GetActiveCamera();
		if (pTemp != NULL)
		{
			// Set up button dimensions and offset
			float bWidth = 200.0f;
			float bHeight = 68.5f;
			float offsetX = -(bWidth / 2);
			float offsetY = -(bHeight / 2) + 50;

			// Create a start button and initialize it, then add to vector
			Button *pTemp = g_Engine->GetFactory()->CreateObject<Button>();
			if (pTemp)
			{
				// Initialize the button
				pTemp->Initialize("Calibri", 36, offsetX, offsetY, 
					bWidth, bHeight, "START", BUTTONTYPES::START_BUTTON, BUTTONTEXTURES::MENU_BUTTON_TEXTURE, D3DCOLOR_XRGB(255, 255, 255));

				uiObjects.push_back(pTemp);
			}

			// Create a exit button and initialize it, then add to vector
			pTemp = g_Engine->GetFactory()->CreateObject<Button>();
			if (pTemp)
			{
				// Offset this button so that it is 10p below the "START"
				offsetY += bHeight + 10;

				// Initialize the button
				pTemp->Initialize("Calibri", 36, offsetX, offsetY,
					bWidth, bHeight, "EXIT", BUTTONTYPES::EXIT_BUTTON, BUTTONTEXTURES::MENU_BUTTON_TEXTURE, D3DCOLOR_XRGB(255, 255, 255));

				uiObjects.push_back(pTemp);
			}
		}

		// Set the UI Objects
		g_Engine->GetUIManager()->SetUIObjects(uiObjects);
	}


	UIManager::UIManager()
	{
		
	}


	UIManager::~UIManager() 
	{
		// Release any remaining objects
		if (!_uiObjects.empty())
			PurgeUIObjects();
	}


	void UIManager::LoadUI(unsigned int levelID)
	{
		// Determine which load function to use
		switch (levelID)
		{
		case UI_LEVELS::STANDARD_GAMEPLAY_UI:
			Standard_Gameplay_UI();
			break;

		case UI_LEVELS::MAIN_MENU_UI:
			Main_Menu_UI();
			break;

		default:
			debug << "\tFailed to load UI, levelID out of range" << std::endl;
			break;
		}
	}


	void UIManager::Update(float deltaTime)
	{
		/*
			Currently no UI objects use their update function, as their positions are
			determined in the render function instead. However, just in case it is added
			in the future, their update functions are called each frame.
		*/
		// Call update for all UI_Objects
		for (_uiIt = _uiObjects.begin(); _uiIt != _uiObjects.end(); ++_uiIt)
		{
			/*
				Dynamically cast in IGameObject to ensure each
				object can call the Update() function
			*/
			IGameObject *pTemp = NULL;
			pTemp = dynamic_cast<IGameObject*>((*_uiIt));

			if (pTemp)
				pTemp->Update(deltaTime);
		}
	}


	void UIManager::Render()
	{
		if (g_Engine->GetActiveCamera())
		{
			// Call render for all UI_Objects
			for (_uiIt = _uiObjects.begin(); _uiIt != _uiObjects.end(); ++_uiIt)
			{
				/*
			Dynamically cast in IRenderableObject to ensure each
			object can call the Render() function
			*/
				IRenderableObject *pTemp = NULL;
				pTemp = dynamic_cast<IRenderableObject*>((*_uiIt));

				if (pTemp)
					pTemp->Render();
			}
		}
		else
			debug << "\tNo active camera is set, UI cannot render" << std::endl;
	}


	void UIManager::Shutdown()
	{
		debug << "\tUI shutting down..." << std::endl;

		// Release memory used by UI
		if (!_uiObjects.empty())
		{
			for (_uiIt = _uiObjects.begin(); _uiIt != _uiObjects.end();)
			{
				delete (*_uiIt);
				_uiIt = _uiObjects.erase(_uiIt);
			}
			_uiObjects.clear();
		}
		
		if (_uiObjects.empty())
			debug << "\tUI shutdown" << std::endl;
		else
			debug << "\tError shutting down UI" << std::endl;
	}


	//////////////////////
	// Utility Functions
	//////////////////////
	void UIManager::SetUIObjects(std::vector<IUI_Object*> uiObjects)
	{
		// Deallocate any memory before switching to the new vector
		for (_uiIt = _uiObjects.begin(); _uiIt != _uiObjects.end();)
		{
			delete (*_uiIt);
			_uiIt = _uiObjects.erase(_uiIt);
		}

		// Shallow copy the vector to preserve the pointers
		_uiObjects = uiObjects;
	}


	void UIManager::PurgeUIObjects()
	{
		// Deallocate any memory before switching to the new vector
		for (_uiIt = _uiObjects.begin(); _uiIt != _uiObjects.end();)
		{
			delete (*_uiIt);
			_uiIt = _uiObjects.erase(_uiIt);
		}
	}
}
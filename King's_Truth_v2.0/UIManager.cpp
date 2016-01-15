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
		#pragma region UIObjectCreation
		if (g_Engine->GetActiveCamera() != nullptr)
		{
			// Set up label dimensions and offset
			float lWidth = 200.0f;
			float lHeight = 75.0f;
			float offsetX = -((SCREENW / 2) * g_Engine->GetActiveCamera()->GetZoomFactor()) + 10;
			float offsetY = -((SCREENH / 2) * g_Engine->GetActiveCamera()->GetZoomFactor()) + 7.5f;

			// Health label
			Label* pTempLabel = g_Engine->GetFactory()->CreateObject<Label>();
			if (pTempLabel)
			{
				pTempLabel->Initialize("Calibri", 14, offsetX, offsetY,
					"Health:", LABELTEXTURES::STANDARD_LABEL_TEXTURE);

				uiObjects.push_back(pTempLabel);
				pTempLabel = nullptr;
			}
			else
				debug << "\tFailed to create 'Label - Health' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Hearts - 1
			PicBox* pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 40;
				pTempPic->Initialize(16, 16, offsetX, offsetY,
					true, "heart.png", "heart");
			
				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - Heart' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Hearts - 2
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 16;
				pTempPic->Initialize(16, 16, offsetX, offsetY, 
					true, "heart.png", "heart");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - Heart' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Hearts - 3
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 16;
				pTempPic->Initialize(16, 16, offsetX, offsetY, 
					true, "heart.png", "heart");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - Heart' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Hearts - 4
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 16;
				pTempPic->Initialize(16, 16, offsetX, offsetY,
					true, "heart.png", "heart");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - Heart' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Hearts - 5
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 16;
				pTempPic->Initialize(16, 16, offsetX, offsetY,
					true, "heart.png", "heart");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - Heart' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Lives Label
			pTempLabel = g_Engine->GetFactory()->CreateObject<Label>();
			if (pTempLabel)
			{
				offsetX += 25;
				pTempLabel->Initialize("Calibri", 14, offsetX, offsetY,
					"Lives:", LABELTEXTURES::STANDARD_LABEL_TEXTURE);

				uiObjects.push_back(pTempLabel);
				pTempLabel = nullptr;
			}
			else
				debug << "\tFailed to create 'Label - Lives' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Player lives icon - 1
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 32;
				pTempPic->Initialize(16, 16, offsetX, offsetY,
					true, "player_icon.png", "player_life");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - PlayerIcon' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Player lives icon - 2
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 16;
				pTempPic->Initialize(16, 16, offsetX, offsetY,
					true, "player_icon.png", "player_life");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - PlayerIcon' in STANDARD_GAMEPLAY_UI" << std::endl;

			// Player lives icon - 3
			pTempPic = g_Engine->GetFactory()->CreateObject<PicBox>();
			if (pTempPic)
			{
				offsetX += 16;
				pTempPic->Initialize(16, 16, offsetX, offsetY,
					true, "player_icon.png", "player_life");

				uiObjects.push_back(pTempPic);
				pTempPic = nullptr;
			}
			else
				debug << "\tFailed to create 'PicBox - PlayerIcon' in STANDARD_GAMEPLAY_UI" << std::endl;
		}
		#pragma endregion

		// Set the UI Objects
		SetUIObjects(uiObjects);
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
		#pragma region UIObjectCreation
		if (g_Engine->GetActiveCamera() != nullptr)
		{
			// Set up button dimensions and offset
			float bWidth = 200.0f;
			float bHeight = 64.5f;
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
				pTemp = nullptr;
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
				pTemp = nullptr;
			}
		}
		#pragma endregion

		// Set the UI Objects
		SetUIObjects(uiObjects);
	}


	UIManager::UIManager()
	{
		// Register event listeners
		g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_DAMAGED);
		g_Engine->GetEventManager()->RegisterListener(this, Events::PLAYER_DEAD);
	}


	UIManager::~UIManager() 
	{
		// Release any remaining objects
		if (!_uiObjects.empty())
			PurgeUIObjects();

		// Purge event listeners
		g_Engine->GetEventManager()->PurgeListener(ID, Events::PLAYER_DAMAGED);
		g_Engine->GetEventManager()->PurgeListener(ID, Events::PLAYER_DAMAGED);
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
			IGameObject *pTemp = nullptr;
			pTemp = dynamic_cast<IGameObject*>((*_uiIt));

			if (pTemp)
				pTemp->Update(deltaTime);
		}
	}


 	void UIManager::HandleEvent(IEvent *e)
	{
		//////////////////////
		// Player Damaged
		//////////////////////
		if (e->Event_Type == Events::PLAYER_DAMAGED)
		{
			// Cast to proper event type
			PlayerDamagedEvent *pEvent = static_cast<PlayerDamagedEvent*>(e);
			if (pEvent)
			{
				// Create temp object pointers
				IGameObject *pTemp = nullptr;
				PicBox *tempPic = nullptr;

				// Deactivate hearts based on damage dealt
				for (int i = 0; i < pEvent->damage; ++i)
				{
					// Ensure temp pointers are null
					pTemp = nullptr;
					tempPic = nullptr;

					// Run backwards through UIObjects vector
					for (_ruiIt = _uiObjects.rbegin(); _ruiIt != _uiObjects.rend(); ++_ruiIt)
					{
						// Cast to GameObject
						pTemp = dynamic_cast<IGameObject*>((*_ruiIt));

						if (pTemp)
						{
							if (pTemp->tag == "heart")
							{
								// Cast to picBox
								tempPic = dynamic_cast<PicBox*>((*_ruiIt));
								if (tempPic)
								{
									if (tempPic->IsActive())
									{
										// Deactivate
										tempPic->SetActive(false);
										break;
									}
									else
									{
										// Reset tempPic
										tempPic = nullptr;
									}
								}
							}
						}
					}
				}

				//*************** FIX DEBUG FILE FOR PICBOX ***************//
				// Check if player health <= 0
				if (g_Engine->GetPlayer()->GetHealth() <= 0)
				{
					// Dispatch a new event
					PlayerDeadEvent *pEvent = new PlayerDeadEvent();
					g_Engine->GetEventManager()->DispatchEvent(pEvent);
				}
			}
		}

		//////////////////////
		// Player Dead
		//////////////////////
		if (e->Event_Type == Events::PLAYER_DEAD)
		{
			debug << "\t\tPlayer Died." << std::endl;
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
				IRenderableObject *pTemp = nullptr;
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
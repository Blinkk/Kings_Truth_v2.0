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
	void Level1()
	{
		std::vector<IUI_Object*> uiObjects;
		Label *testLabel = new Label();
		if (testLabel)
			testLabel->InitializeUIObject("Calibri", 24, SCREENW / 2, SCREENH / 2, "TESTING", D3DCOLOR_XRGB(255, 255, 255));

		uiObjects.push_back(testLabel);

		// Set the UI Objects
		g_Engine->GetUIManager()->SetUIObjects(uiObjects);
	}


	UIManager::UIManager()
	{
		// Ensure there are no UI_Objects in the vector (somehow)
		if (!_uiObjects.empty())
		{
			for (_uiIt = _uiObjects.begin(); _uiIt != _uiObjects.end();)
			{
				delete (*_uiIt);
				_uiIt = _uiObjects.erase(_uiIt);
			}
			_uiObjects.clear();
		}
	}


	UIManager::~UIManager() {}


	void UIManager::LoadUI(unsigned int levelID)
	{
		// Determine which load function to use
		switch (levelID)
		{
		case LEVEL_ONE_UI:
			uiLvlPtr = &Level1;
		}
		// Call the function that the pointer points to
		uiLvlPtr();
	}


	void UIManager::HandleEvent(IEvent* e)
	{

	}


	void UIManager::Update(float deltaTime)
	{
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


	void UIManager::Shutdown()
	{
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
	}


	//////////////////////
	// Utility Functions
	//////////////////////
}
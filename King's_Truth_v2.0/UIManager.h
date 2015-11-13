/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef UI_H
#define UI_H
#include "IGameObject.h"
#include "IRenderableObject.h"
#include <vector>

// UI_Object headers
#include "Label.h"

enum UI_Levels
{
	LEVEL_ONE_UI = 0
};

namespace Smoke
{
	class UIManager : public IGameObject, IRenderableObject
	{
	private:
		UIManager();
		std::vector<IUI_Object*> _uiObjects;
		std::vector<IUI_Object*>::iterator _uiIt;

	public:
		static UIManager& GetInstance()
		{
			UIManager *pInstance = NULL;

			if (!pInstance)
			{
				pInstance = new UIManager();
			}

			return (*pInstance);
		}

		~UIManager();
		void LoadUI(unsigned int levelID);
		void HandleEvent(IEvent*) override;
		void Update(float deltaTime) override;
		void Render() override;
		void Shutdown();

		/*
			This function that this function pointer points to
			will be called in the LoadLevel function
		*/
		void(*uiLvlPtr)();

		//////////////////////
		// Utility Functions
		//////////////////////
		void DrawDebug();
		void SetUIObjects(std::vector<IUI_Object*> uiObjects) { _uiObjects = uiObjects; }
	};
}

#endif
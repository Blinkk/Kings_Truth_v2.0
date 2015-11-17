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
	STANDARD_GAMEPLAY_UI = 0
};

namespace Smoke
{
	class UIManager : public IGameObject, IRenderableObject
	{
	private:
		UIManager();
		std::vector<IUI_Object*> _uiObjects;
		std::vector<IUI_Object*>::iterator _uiIt;

		///////////////////////
		// UI Setup Functions
		///////////////////////
		// Note: Called internally only, use LoadUI()
		void Standard_Gameplay_UI();

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

		/*
			This function is dependent on there being an
			active camera set in the global g_Engine reference.
			Make sure to set this prior to calling this function,
			otherwise no UIObjects will be created.
		*/
		void LoadUI(unsigned int levelID);

		/*
			This function calls the render function for
			each UIObject in the vector.

			Note: UI elements will not render if there is no
			active camera set in the global reference. (g_Engine->SetActiveCamera(...))
		*/
		void Render() override;

		void HandleEvent(IEvent*) override;
		void Update(float deltaTime) override;
		void Shutdown();
		

		//////////////////////
		// Utility Functions
		//////////////////////
		void DrawDebug();
		void SetUIObjects(std::vector<IUI_Object*> uiObjects) { _uiObjects = uiObjects; }
	};
}

#endif
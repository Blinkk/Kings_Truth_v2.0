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
#include "Button.h"
#include "PicBox.h"

enum UI_LEVELS
{
	STANDARD_GAMEPLAY_UI = 0,
	MAIN_MENU_UI
};

/*
	This enum is merely to avoid having to include the entire contents
	of the GameManager.h when all we need access to is the LEVELS enum.

	Note: This enum must match the one in the GameManager.h in order to function
	properly.

	TODO: Make this make more sense....
*/
enum GAME_LEVELS
{
	GAME_LEVEL_MAIN_MENU = 0,
	GAME_LEVEL_ONE = 1,
};

namespace Smoke
{
	class UIManager
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
		void Main_Menu_UI();

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
		void Render();

		void HandleEvent(IEvent*);
		void Update(float deltaTime);
		void Shutdown();
		

		//////////////////////
		// Utility Functions
		//////////////////////
		void DrawDebug();
		void SetUIObjects(std::vector<IUI_Object*> uiObjects);
		void PurgeUIObjects();
		void UpdateMousePos();
	};
}

#endif
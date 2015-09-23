/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef UI_H
#define UI_H
#include "Font.h"

namespace Smoke
{
	class UIManager
	{
	private:
		Font _fontObject;		// Main font object for UI

		UIManager();

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
		bool Initialize(std::string fontName, int fontSize);
		void Render();
		void Shutdown();

		//////////////////////
		// Utility Functions
		//////////////////////
		void DrawDebug();
	};
}

#endif
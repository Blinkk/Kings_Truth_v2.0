/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

namespace Smoke
{
	UIManager::UIManager()
	{
		
	}


	UIManager::~UIManager() {}


	bool UIManager::Initialize(std::string fontName, int fontSize)
	{
		// Create the font object
		_fontObject = Font(fontName, fontSize);

		return true;
	}


	void UIManager::Render()
	{
		// Render debug information (comment out to remove)
	}


	void UIManager::Shutdown()
	{
		// Release memory used by UI
	}


	//////////////////////
	// Utility Functions
	//////////////////////
}
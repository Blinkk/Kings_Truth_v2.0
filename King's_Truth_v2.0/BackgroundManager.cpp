#include "Engine_Core.h"

namespace Smoke
{
	BackgroundManager::BackgroundManager()
	{

	}


	BackgroundManager::~BackgroundManager()
	{
		// If there are remaining backgrounds, release them
		if (!_backgrounds.empty())
			PurgeBackgrounds();
	}


	void BackgroundManager::Update(float deltaTime)
	{
		// Currently, no backgrounds are capable of calling Update
	}


	void BackgroundManager::Render()
	{
		for (_bIt = _backgrounds.begin(); _bIt != _backgrounds.end(); ++_bIt)
		{
			// Render each background if it is able to render
			IRenderableObject *pTemp = dynamic_cast<IRenderableObject*>((*_bIt));
			
			if (pTemp)
				pTemp->Render();
		}
	}


	void BackgroundManager::AddBackground(IBackground *bg)
	{
		if (bg != NULL)
			_backgrounds.push_back(bg);
		else
			debug << "\tFailed to add a background to vector" << std::endl;
	}


	void BackgroundManager::PurgeBackgrounds()
	{
		if (!_backgrounds.empty())
		{
			for (_bIt = _backgrounds.begin(); _bIt != _backgrounds.end();)
			{
				// Delete the object
				delete (*_bIt);
				_bIt = _backgrounds.erase(_bIt);
			}
		}
	}
}
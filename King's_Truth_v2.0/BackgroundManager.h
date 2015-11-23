#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H
#include <vector>
#include "IBackground.h"

namespace Smoke
{
	class BackgroundManager
	{
	private:
		/*
			Having a vector of background will allow for
			layering the backgrounds. Each background in
			the vector will be rendered on each main Render()
			call. 

			Note: Add backgrounds to vector in level creation
			functions (GameManager.cpp)
		*/
		std::vector<IBackground*> _backgrounds;
		std::vector<IBackground*>::iterator _bIt;

		// Constructor
		BackgroundManager();

	public:
		static BackgroundManager& GetInstance()
		{
			BackgroundManager *pInstance = NULL;

			if (!pInstance)
			{
				pInstance = new BackgroundManager();
			}

			return (*pInstance);
		}

		~BackgroundManager();

		/*
			These function call the update and render
			functions for each background in the vector

			Note: ONLY CALL THESE IN THEIR RESPECTIVE CYCLES
		*/
		void Update(float deltaTime);
		void Render();

		/*
			Add a new background to the vector

			Note: Only call this in level creation functions
		*/
		void AddBackground(IBackground *bg);

		/*
			Remove all current backgrounds in vector.

			Note: Only call this at the end of a level (g_Manager->UnloadLevel())
		*/
		void PurgeBackgrounds();

		
		

	};
}

#endif
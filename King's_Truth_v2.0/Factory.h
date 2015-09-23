#ifndef FACTORY_H
#define FACTORY_H

/*
	Note: Had to include this to use NULL... not sure why since
	not a single other file had a problem.

	TODO: Fix this (find out why this is happeneing)
*/
#include <stdlib.h>

namespace Smoke
{
	class Factory
	{
	private:
		Factory();

	public:
		static Factory& GetInstance()
		{
			Factory *pInstance = NULL;

			if (!pInstance)
				pInstance = new Factory();

			return (*pInstance);
		}

		~Factory();

		/////////////////////////////////
		// Templated creation function
		/////////////////////////////////
		template <class T>
		inline T* CreateObject();
	};	// End of class

	
	//////////////////////////////////
	// Template function definition
	//
	// TODO: Test the bloat of 
	// the .exe from having this here
	//////////////////////////////////
	template <class T>
	T* Factory::CreateObject()
	{
		T* pTemp = NULL;

		if (!pTemp)
			pTemp = new T();

		return pTemp;
	}
}	// End of namespace

#endif
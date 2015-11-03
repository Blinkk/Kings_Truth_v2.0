#ifndef FACTORY_H
#define FACTORY_H

namespace Smoke
{
	class Factory
	{
	private:
		/*
			This is the ID that will be assigned to each
			new GameObject created by the factory. This will
			correspond with their position in the main 
			GameObject vector for each level.

			This number is also used in the event system
		*/
		unsigned int _objectID;

		/*
			This function generates a new objectID
			and assigns it to newly created GameObjects.

			Note: This function should only be used within
			this class and therefore should remain private.
		*/
		unsigned int GenerateObjectID();

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

		/////////////////////////////////
		// Accessors / Mutators
		/////////////////////////////////
		void ResetObjectID();

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

		// Assign new object an ID
		IGameObject* pTempObj = dynamic_cast<IGameObject*>(pTemp);
		if (pTempObj)
		{
			pTempObj->ID = GenerateObjectID();
		}

		return pTemp;
	}
}	// End of namespace

#endif
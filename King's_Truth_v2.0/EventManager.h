/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "Delegate.h"
#include "IGameObject.h"
#include <queue>
#include <map>

////////////////////////////////////////////////////////////////
// A variation of Jorge Morales' 
// DirectX 9 Framework Event System -
// https://ebnr.visualstudio.com/DefaultCollection/SG%20450
////////////////////////////////////////////////////////////////

namespace Smoke
{
	typedef std::map<unsigned int, Delegate> Listeners;		// Typedef Listeners for easier syntax

	////////////////////////////////////////
	// Class to dispatch all events
	////////////////////////////////////////
	class EventManager
	{
	private:

		/////////////////////////////////////////////////////////////////////
		// Registrants stores Delegates that need to receive events.
		// 
		// This is done by creating a map of Registrants, of which each
		// element is a map of Delegates. Events are passed through the map
		// of delegates until it is claimed, or there are no more delegates 
		// left in the map.
		/////////////////////////////////////////////////////////////////////
		std::map<unsigned int, Listeners> Registrants;
		 
		std::queue<IEvent*> EventQueue;

		/////////////////////////////////////////////////////////////////////
		// Creates, and returns, a Delegate out of the passed pointer so that
		// the object can be stored and receive Events.
		/////////////////////////////////////////////////////////////////////
		Delegate PackageListener(IGameObject* pIGO);

		/////////////////////////////////////////////////////////////////////
		// Stores a Delegate into Registrants to allow it to receive Events of
		// type eventCode
		/////////////////////////////////////////////////////////////////////
		void StoreListener(Delegate, unsigned int eventCode);

		EventManager();
		
	public:
		~EventManager();
		void Shutdown();					// Shutdown the event manager

		static EventManager& GetInstance()
		{
			static EventManager* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new EventManager();
			}

			return (*pInstance);
		}

		/////////////////////////////////////////////////////////////////////
		// Call this function any time you need to register an object with 
		// the event system.
		/////////////////////////////////////////////////////////////////////
		void RegisterListener(IGameObject* pIGO, unsigned int eventCode);


		// Distributes the receieved event to any listeners registered for it
		void DispatchEvent(IEvent* pEvent);

		/////////////////////////////////////////////
		// Purges the entire contents of Registrants
		/////////////////////////////////////////////
		void PurgeAllListeners();

		// Purge a specific listener from a given event listing
		void PurgeListener(unsigned int ID, unsigned int eventCode);

		// Process any requests that have been back-logged
		void Update();

	};	// End of class
}	// End of namespace

#endif
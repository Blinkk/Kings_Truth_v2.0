/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

////////////////////////////////////////////////////////////////
// A variation of Jorge Morales' 
// DirectX 9 Framework Event System -
// https://ebnr.visualstudio.com/DefaultCollection/SG%20450
////////////////////////////////////////////////////////////////

namespace Smoke
{
	EventManager::EventManager()  
	{
		for (int i = 0; i <= Events::MAX; ++i)
		{
			Registrants[i] = Listeners();
		}
	}

	void EventManager::StoreListener(Delegate del, unsigned int eventCode)
	{
		Registrants[eventCode][del.ID] = del;
	}


	Delegate EventManager::PackageListener(IGameObject* pIGO)
	{
		Delegate D = Delegate::makeDelegateFromFunction<IGameObject, &IGameObject::HandleEvent>(pIGO, pIGO->ID);

		return D;
	}

	void EventManager::RegisterListener(IGameObject* pIGO, unsigned int eventCode)
	{
		StoreListener(PackageListener(pIGO), eventCode);
	}

	void EventManager::DispatchEvent(IEvent* pEvent)
	{
		EventQueue.push(pEvent);
	}

	void EventManager::PurgeAllListeners()
	{
		for (unsigned int i = 0; i < Registrants.size(); ++i)
		{
			Registrants[i].erase(Registrants[i].begin(), Registrants[i].end());
		}
	}

	void EventManager::PurgeListener(unsigned int ID_NUMBER, unsigned int eventCode)
	{
		// Remove the specified listener
		Registrants[eventCode].erase(ID_NUMBER);
	}

	void EventManager::Update()
	{
		// Dispatch all events
		while (EventQueue.empty() != true)
		{
			// More convienent reference to the Event
			IEvent* pEvent = EventQueue.front();

			if (pEvent == NULL)
			{
				// TODO: Create proper error message because this should not happen
				return;
			}

			Listeners::iterator Iter = Registrants[pEvent->Event_Type].begin();

			// Iterate through the 
			while (pEvent->handledErase != true && Iter != Registrants[pEvent->Event_Type].end())
			{
				(*Iter).second(pEvent);

				++Iter;
			}

			delete pEvent;
			pEvent = NULL;
			EventQueue.pop();
		}
	}

	void EventManager::Shutdown()
	{
		this->PurgeAllListeners();
	}
	

	EventManager::~EventManager()
	{
		// Shutdown function manages 
		// memory deallocation
	}
}
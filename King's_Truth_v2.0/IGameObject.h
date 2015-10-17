/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef GAMEOBJ_H
#define GAMEOBJ_H
#include "Event.h"


/////////////////////////////////////////////////////////////////////////////////
// Interface that all Game Objects should inherit from.
// 
// Contains the means for objects to update internal logic, identify themselves,
// and receive events that they are registered to listen to.
/////////////////////////////////////////////////////////////////////////////////
namespace Smoke
{
	class IGameObject
	{
	public:
		// Identification number used for event system
		unsigned int ID;

		// Determines how the object uses information received from events
		virtual void HandleEvent(IEvent*) = 0;

		/////////////////////////////////////////////////////////
		// Function in which any object logic should be placed.
		// 
		// Called only when the Game::Update function is called.
		/////////////////////////////////////////////////////////
		virtual void Update(float deltaTime) = 0;

		// Force objects have their own destructors to manage any memory that be used
		virtual ~IGameObject() {}
	};
}
#endif
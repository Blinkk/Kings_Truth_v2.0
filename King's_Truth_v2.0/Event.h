/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef EVENT_H
#define EVENT_H

namespace Smoke
{
	/////////////////////////////////////////////////////////////////////
	// A listing of all events in the game.
	// 
	// Use this namespace when determining type of event received by a listener
	// - Example: pEvent->Event_Type == Event_Listings::EVENT_PLAYER_INPUT
	/////////////////////////////////////////////////////////////////////
	namespace Events
	{
		const unsigned int PLAYER_INPUT = 0;
		const unsigned int PLAYER_COLLISION = 1;
		const unsigned int CLICK_DOWN = 2;
		const unsigned int CLICK_UP = 3;
		const unsigned int ENDLEVEL = 4;
		const unsigned int ENDPROGRAM = 5;

		const unsigned int MAX = ENDPROGRAM;
	}

	////////////////////
	// EVENT INTERFACE
	////////////////////
	class IEvent
	{
	public:
		/////////////////////////////////////////////////////////////////////
		// Value used by listeners to determine what type of event they've
		// received.
		/////////////////////////////////////////////////////////////////////
		unsigned int Event_Type;


		/////////////////////////////////////////////////////////////////////
		// Determines whether an event should continue to be distributed to
		// other listeners in the Event System or not
		/////////////////////////////////////////////////////////////////////
		bool handledErase;

		IEvent()
		{
			handledErase = false;
		}

	};


	///////////////////
	// Event classes
	///////////////////
	class PlayerInputEvent : public IEvent
	{
	public:
		bool up;
		bool left;
		bool right;
		bool down;
		bool attack;
		bool jump;

		PlayerInputEvent()
		{
			Event_Type = Events::PLAYER_INPUT;

			up = false;
			left = false;
			right = false;
			down = false;
			attack = false;
		}
	};


	class PlayerCollisionEvent : public IEvent
	{
	public:
		PlayerCollisionEvent()
		{
			Event_Type = Events::PLAYER_COLLISION;
		}
	};


	class ClickDownEvent : public IEvent
	{
	public:
		bool left;
		bool right;
		float mousePosX;
		float mousePosY;

		ClickDownEvent()
		{
			Event_Type = Events::CLICK_DOWN;

			left = false;
			right = false;
			mousePosX = 0;
			mousePosY = 0;
		}
	};


	class ClickUpEvent : public IEvent
	{
	public:
		bool left;
		bool right;
		float mousePosX;
		float mousePosY;

		ClickUpEvent()
		{
			Event_Type = Events::CLICK_UP;

			left = false;
			right = false;
			mousePosX = 0;
			mousePosY = 0;
		}
	};


	class EndLevelEvent : public IEvent
	{
	public:
		unsigned int newLevel;

		EndLevelEvent()
		{
			Event_Type = Events::ENDLEVEL;

			newLevel = 0;
		}
	};
}	// End of namespace

#endif
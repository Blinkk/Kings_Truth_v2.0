#include "Engine_Core.h"
#include "Keyboard.h"

namespace Smoke
{
	Keyboard::Keyboard()
	{

	}


	Keyboard::~Keyboard()
	{

	}


	void Keyboard::ProcessInput(const unsigned int mask)
	{
		////////////////////////////////////////////////////////////////
		// Process the received bit-mask and send any applicable events
		// 
		// PLAYER RELATED INPUT
		// 1 = Move up
		// 2 = Move left
		// 4 = Move down
		// 8 = Move right
		// 16 = Attack
		////////////////////////////////////////////////////////////////
		if (mask > 0)
		{
			// Check first 5 bits
			int maskTest = mask << 26;

			if (maskTest > 0)
			{
				// If input is detected, create a new event
				PlayerInputEvent* pTemp = new PlayerInputEvent();

				//////////////////////////////////////////
				// Set the event object's value based on
				// the input mask passed to this function
				//////////////////////////////////////////
				pTemp->up = (mask & 1);
				pTemp->left = (mask & 2);
				pTemp->down = (mask & 4);
				pTemp->right = (mask & 8);
				pTemp->attack = (mask & 16);

				// Dispatch the event to the event manager
				g_Engine->GetEventManager()->DispatchEvent(pTemp);
			}
		}
	}
}
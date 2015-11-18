#include "Mouse.h"
#include "Engine_Core.h"

namespace Smoke
{
	Mouse::Mouse()
	{
		_buttonDown = false;
		_leftButtonDown = false;
		_rightButtonDown = false;
	}


	Mouse::~Mouse()
	{

	}


	void Mouse::ProcessInput(const unsigned int mask)
	{
		////////////////////////////////////////////////////////////////
		// Process the received bit-mask and send any applicable events
		// 
		// MOUSE RELATED INPUT
		// 1 = Left Click
		// 2 = Right Click
		////////////////////////////////////////////////////////////////
		if (mask > 0)
		{
			// Check first 2 bits
			int maskTest = mask << 29;

			if (maskTest > 0)
			{
				// Update mouse position
				POINT mousePos = POINT();
				GetCursorPos(&mousePos);
				ScreenToClient(g_Engine->GetWindowHandle(), &mousePos);

				// If input is detected, create a new event
				ClickDownEvent* pTemp = new ClickDownEvent();

				// Determine which button was clicked
				pTemp->left = (mask & 1);
				pTemp->right = (mask & 2);

				// Store the current button press flag for later
				_leftButtonDown = pTemp->left;
				_rightButtonDown = pTemp->right;

				// Store mouse position in event
				pTemp->mousePosX = mousePos.x;
				pTemp->mousePosY = mousePos.y;

				// Dispatch the event to the event manager
				g_Engine->GetEventManager()->DispatchEvent(pTemp);

				// Set the button flag for (CLICK_UP events)
				_buttonDown = true;
			}
		}
		else
		{
			if (_buttonDown)
			{
				// Update mouse position
				POINT mousePos = POINT();
				GetCursorPos(&mousePos);
				ScreenToClient(g_Engine->GetWindowHandle(), &mousePos);

				// If input is detected, create a new event
				ClickUpEvent* pTemp = new ClickUpEvent();

				// Determine which button was clicked
				pTemp->left = _leftButtonDown;
				pTemp->right = _rightButtonDown;

				// Store mouse position in event
				pTemp->mousePosX = mousePos.x;
				pTemp->mousePosY = mousePos.y;

				// Dispatch the event to the event manager
				g_Engine->GetEventManager()->DispatchEvent(pTemp);

				// Reset button flags
				_buttonDown = false;
				_leftButtonDown = false;
				_rightButtonDown = false;
			}
		}
	}
}
/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

namespace Smoke
{
	InputManager::InputManager()
	{
		
	}


	InputManager::~InputManager() {}


	bool InputManager::Initialize()
	{
		// Initialize DirectInput
		if (DirectInput_Initialize())
			return true;
		else
		{
			debug << "\tInput failed to initialize" << std::endl;
			return false;
		}

		// Register this object for events here...
	}


	void InputManager::Update(float deltaTime)
	{
		// Update DirectInput devices
		DirectInput_Update();

		////////////////////////
		// Update IInputDevices
		////////////////////////
		if (mouse)
		{
			unsigned int mouseMask = 0;

			if (mouseState.rgbButtons[0] & 0x80)
			{
				mouseMask |= 1;
			}

			if (mouseState.rgbButtons[1] & 0x80)
			{
				mouseMask |= 2;
			}

			// Attempt to Update the object
			IGameObject* pTemp = dynamic_cast<IGameObject*>(mouse);
			if (pTemp)
			{
				pTemp->Update(deltaTime);
			}

			// Pass the input mask to the InputDevice to be processed
			mouse->ProcessInput(mouseMask);
		}

		if (keyboard)
		{
			unsigned int keyboardMask = 0;

			if (keyboardDIKCodes.size() != 0)
			{
				///////////////////////////////////////////////////////////////////
				// This loop iterates through the DIK Key vector and checks to see
				// if any input has occured.
				// 
				// If input has occured, the mask is bitwise OR'd by 1 bit-shifted
				// left by the value of i.
				///////////////////////////////////////////////////////////////////
				for (int i = 0; i < keyboardDIKCodes.size(); ++i)
				{
					if ((bool)(keyState[keyboardDIKCodes[i]] & 0x80))
					{
						keyboardMask |= (1 << i);
					}
				}

				// Attempt to Update the object
				IGameObject* pTemp = dynamic_cast<IGameObject*>(keyboard);
				if (pTemp)
				{
					pTemp->Update(deltaTime);
				}

				// Pass the input mask to the InputDevice to be processed
				keyboard->ProcessInput(keyboardMask);
			}
		}
	}


	void InputManager::Render()
	{

	}


	bool InputManager::DirectInput_Initialize()
	{
		// Create DirectInput object
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&di, nullptr);

		// Initialize keyboard
		di->CreateDevice(GUID_SysKeyboard, &diKeyboard, nullptr);
		diKeyboard->SetDataFormat(&c_dfDIKeyboard);
		diKeyboard->SetCooperativeLevel(g_Engine->GetWindowHandle(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		diKeyboard->Acquire();

		// Clear key array
		memset(keyState, 0, 256);

		// Initialize mouse
		di->CreateDevice(GUID_SysMouse, &diMouse, nullptr);
		diMouse->SetDataFormat(&c_dfDIMouse);
		diMouse->SetCooperativeLevel(g_Engine->GetWindowHandle(),
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		diMouse->Acquire();
		g_Engine->GetDevice()->ShowCursor(false);

		return true;
	}


	void InputManager::DirectInput_Update()
	{
		// Poll state of the keyboard
		diKeyboard->Poll();
		if (!SUCCEEDED(diKeyboard->GetDeviceState(256, (LPVOID)&keyState)))
		{
			// Keyboard device lost, try to re-acquire
			diKeyboard->Acquire();
		}

		// Poll state of the mouse
		diMouse->Poll();
		if (!SUCCEEDED(diMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)))
		{
			// Mouse device lost, try to re-acquire
			diMouse->Acquire();
		}
	}


	void InputManager::Shutdown()
	{
		int bugs = 0;
		debug << "\tInput shutting down..." << std::endl;

		// Release DirectInput devices			
		if (diMouse)
		{
			diMouse->Unacquire();
			if (diMouse->Release() > 0)
			{
				debug << "\t\tFailed to release mouse" << std::endl;
				bugs++;
			}
			diMouse = nullptr;
		}
		if (diKeyboard)
		{
			diKeyboard->Unacquire();
			if (diKeyboard->Release() > 0)
			{
				debug << "\t\tFailed to release keyboard" << std::endl;
				bugs++;
			}
			diKeyboard = nullptr;
		}
		if (di->Release() > 0)
		{
			debug << "\t\tFailed to release direct input device" << std::endl;
			bugs++;
		}

		// Release IInputDevices
		if (keyboard)
		{
			delete keyboard;
			keyboard = nullptr;
		}

		if (mouse)
		{
			delete mouse;
			mouse = nullptr;
		}

		if (mouse == nullptr && keyboard == nullptr)
			debug << "\tInput shutdown successfully" << std::endl;
		else
			debug << "\tError shutting down input" << std::endl;
	}

}



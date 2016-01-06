/**********************************
*  Programmer: Austin Ivicevic / Daniel Flores
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef INPUT_H
#define INPUT_H
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <vector>
#include "IInputDevice.h"

namespace Smoke
{
	class InputManager
	{
	private:
		// Direct Input
		IDirectInput8 *di;
		LPDIRECTINPUTDEVICE8 diKeyboard;
		LPDIRECTINPUTDEVICE8 diMouse;
		DIMOUSESTATE mouseState;
		
		// Keyboard input keys array
		char keyState[256];

		// Input devices (Process Input)
		IInputDevice *keyboard;
		IInputDevice *mouse;

		// Input to check for (keyboard)
		std::vector<int> keyboardDIKCodes;

		// DirectInput functions
		bool DirectInput_Initialize();
		void DirectInput_Update();

		InputManager();

	public:
		~InputManager();

		static InputManager& GetInstance()
		{
			static InputManager* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new InputManager();
			}

			return (*pInstance);
		}

		bool Initialize();
		void Update(float deltaTime);
		void Render();
		void Shutdown();

		/////////////////////////////
		// Accessors / Mutators
		/////////////////////////////
		void SetDIKKeyboardCodes(std::vector<int> codes) { keyboardDIKCodes = codes; }
		void SetKeyboard(IInputDevice *kb) { keyboard = kb; }
		void SetMouse(IInputDevice *m) { mouse = m; }

		
	};	// End of class
}	// End of namespace

#endif

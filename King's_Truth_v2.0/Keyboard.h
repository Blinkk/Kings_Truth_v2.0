#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "IInputDevice.h"

namespace Smoke
{
	class Keyboard : public IInputDevice
	{
	public:
		Keyboard();
		~Keyboard();

		void ProcessInput(const unsigned int mask) override;
	};
}

#endif
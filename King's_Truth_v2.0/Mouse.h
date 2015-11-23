#ifndef MOUSE_H
#define MOUSE_H
#include "IInputDevice.h"

namespace Smoke
{
	class Mouse : public IInputDevice
	{
	private:
		bool _buttonDown;
		bool _leftButtonDown;
		bool _rightButtonDown;

	public:
		Mouse();
		~Mouse();

		void ProcessInput(const unsigned int mask) override;
	};
}

#endif
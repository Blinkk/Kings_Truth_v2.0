#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H

namespace Smoke
{
	class IInputDevice
	{
	public:
		// Process input for this input device
		virtual void ProcessInput(const unsigned int mask) = 0;	

		// Forces input devices to manage their own memory
		virtual ~IInputDevice(){};			
	};
}

#endif
#include "Engine_Core.h"

namespace Smoke
{
	Factory::Factory()
	{
		// Start ID at 0
		_objectID = 0;
	}


	Factory::~Factory()
	{
		// No memory to be managed
	}


	void Factory::ResetObjectID()
	{
		if (_objectID > 0)
			_objectID = 0;
	}
}
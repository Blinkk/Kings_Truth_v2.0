#ifndef IUIOBJECT_H
#define IUIOBJECT_H
#include <string>
#include "IRenderableObject.h"
#include "IGameObject.h"
#include "2DRenderManager.h"
#include "Vector.h"

enum UI_OBJECT_TYPES
{
	UI_LABEL = 0,
	UI_BUTTON,
	UI_PICBOX,
};

namespace Smoke
{
	class IUI_Object : public IRenderableObject, public IGameObject
	{
	protected:
		/*
			Used to identify the type of UI_Object 
			inheriting from this interface
		*/
		unsigned int _objectType;

		// Camera delta position check value
		Vector2 _cameraPrevPos;

		// Offset from center (camera is centered)
		Vector2 _offsetPosition;

		// Used to render each UI_Object
		TwoDRenderManager Renderer;

	public:
		virtual ~IUI_Object() {};

		/////////////////////////
		// Accessors / Mutators
		/////////////////////////
		unsigned int GetObjectType() { return _objectType; }
		void SetObjectType(unsigned int type) { _objectType = type; }
	};
}

#endif

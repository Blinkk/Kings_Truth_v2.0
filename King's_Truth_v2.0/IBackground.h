#ifndef IBACKGROUND_H
#define IBACKGROUND_H
#include "IRenderableObject.h"
#include "IGameObject.h"
#include "2DRenderManager.h"

namespace Smoke
{
	class IBackground : public IRenderableObject, public IGameObject
	{
	protected:
		TwoDRenderManager Renderer;

	public:
		virtual ~IBackground() {}

		virtual void Initialize(std::string textureToUse, 
			float width, float height, Vector2 pos) = 0;
	};
}

#endif
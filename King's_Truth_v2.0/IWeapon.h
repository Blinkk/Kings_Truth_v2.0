#ifndef IWEAPON_H
#define IWEAPON_H
#include "IRenderableObject.h"
#include "IGameObject.h"
#include "2DRenderManager.h"
using namespace Smoke;

class IWeapon : public IGameObject, public IRenderableObject
{
protected:
	float _range;
	float _damage;

	TwoDRenderManager Renderer;

public:
	virtual ~IWeapon() {}
};

#endif
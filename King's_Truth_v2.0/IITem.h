#ifndef IITEM_H
#define IITEM_H
#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRenderManager.h"
#include "Collider.h"
using namespace Smoke;

enum ITEM_TYPES
{
	DUNGEON_KEY = 1,
	CHEST = 2,
	SWORD = 5,
};

class IItem : public IGameObject, public IRenderableObject
{
protected:
	unsigned int _itemType;
	bool _inInventory;
	Collider hitBox;
	TwoDRenderManager Renderer;

public:
	virtual ~IItem() {}

	virtual void Initialize(float posX, float posY, float rotationInRadians) = 0;
};

#endif
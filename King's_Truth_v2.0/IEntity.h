/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef IENTITY_H
#define IENTITY_H
#include <string>
#include "Collider.h"
#include "IGameObject.h"
#include "IRenderableObject.h"
#include "2DRenderManager.h"
using namespace Smoke;

class IEntity : public IGameObject, public IRenderableObject
{
protected:
	unsigned int _health;

	// Animation
	bool isMoving;
	bool isAttacking;
	unsigned int depth;

	virtual ~IEntity() {}

	// Revert inherited object to idle animation position
	virtual void SetIdle() = 0;

	// Keep inherited object within boundaries (ie. game screen)
	virtual void KeepInBounds() = 0;

	// Keeps track of the entity's direction
	bool facingLeft;
	bool facingUp;

	// TODO: Implement hitBox
	// Hitbox of the inherited object
	Collider hitBox;

	// Handles rendering and animation for inherited object
	TwoDRenderManager Renderer;

	/////////////////////////////////
	// Accessor / Mutator functions
	/////////////////////////////////
	
};	// End of class

#endif
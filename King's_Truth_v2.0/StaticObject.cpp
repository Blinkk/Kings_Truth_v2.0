#include "StaticObject.h"
#include "Engine_Core.h"

StaticObject::StaticObject()
{
	_itemType = ITEM_TYPES::DEFAULT_NONE;

	// This value should never change for static objects
	_inInventory = false;

	// Default hitbox
	hitBox.Initialize(0, 0, 0, 0);
}


StaticObject::~StaticObject()
{

}


void StaticObject::Initialize(float posX, float posY, float rotationInRadians,
	float scaleX, float scaleY, unsigned int frameWidth, unsigned int frameHeight,
	unsigned int numCol, unsigned int startFrame, unsigned int endFrame,
	unsigned int delay, int animDirection, std::string textureToUse)
{
	_itemType = ITEM_TYPES::STATIC_OBJECT;

	// Set up renderer
	Renderer.Initialize(scaleX, scaleY, frameWidth, frameHeight, numCol, 
		startFrame, endFrame, delay, animDirection, rotationInRadians, 
		posX, posY, textureToUse);

	// Initialize hitbox
	hitBox.Initialize(posX, posY, Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());
}


void StaticObject::Initialize(float posX, float posY, float rotationInRadians)
{
	_itemType = ITEM_TYPES::STATIC_OBJECT;

	// Set up renderer
	Renderer.Initialize(1.0f, 1.0f, 16, 16, 12, 7, 7, 0, 0, rotationInRadians, posX, posY, "misc_things.png");

	// Initialize hitbox
	hitBox.Initialize(posX, posY, Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());
}


void StaticObject::Update(float deltaTime)
{

}


void StaticObject::HandleEvent(IEvent *e)
{

}


void StaticObject::Render()
{
	Renderer.Render();
}
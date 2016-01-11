#include "Sword.h"
#include "Engine_Core.h"

Sword::Sword()
{
	_itemType = 0;
	_damage = 0.0f;
	_range = 0.0f;
	_inInventory = false;
	_equipped = false;

	// Default hitbox
	hitBox.Initialize(0, 0, 0, 0);
}


Sword::~Sword()
{

}


void Sword::Initialize(float posX, float posY, float rotationInRadians)
{
	_itemType = ITEM_TYPES::SWORD;

	// Set values for damage/range
	_damage = 1.0f;
	_range = 1.0f;

	// Set up renderer
	Renderer.Initialize(1.0f, 1.0f, 16, 16, 13, 91, 91, 0, 0, rotationInRadians, posX, posY, "items.png");

	// Initialize hitbox
	hitBox.Initialize(posX, posY, Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());

}


void Sword::HandleEvent(IEvent* e)
{

}


void Sword::Update(float deltaTime)
{

}


void Sword::Render()
{
	if (_equipped || !_inInventory)
		Renderer.Render();
}
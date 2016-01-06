#include "Sword.h"
#include "Engine_Core.h"

Sword::Sword()
{
	_damage = 0.0f;
	_range = 0.0f;
	_inInventory = false;

	// Default hitbox
	hitBox.Initialize(0, 0, 0, 0);
}


Sword::~Sword()
{

}


void Sword::Initialize(float posX, float posY, float rotationInRadians)
{
	// Set values for damage/range
	_damage = 1.0f;
	_range = 1.0f;

	// Set up renderer
	Renderer.Initialize(1.0f, 1.0f, 16, 16, 1, 0, 0, 0, 0, rotationInRadians, posX, posY, "sword.png");
}


void Sword::HandleEvent(IEvent* e)
{

}


void Sword::Update(float deltaTime)
{

}


void Sword::Render()
{
	// If renderer has a texture for this object, render it
	if (Renderer.HasTexture())
		Renderer.Render();
}
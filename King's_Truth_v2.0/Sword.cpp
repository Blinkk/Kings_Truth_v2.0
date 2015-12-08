#include "Sword.h"
#include "Engine_Core.h"

Sword::Sword()
{
	_damage = 0.0f;
	_range = 0.0f;
}


Sword::~Sword()
{

}


void Sword::Initialize(float damage, float range)
{
	// Set values for damage/range
	if (damage > 0.0f)
		_damage = damage;
	if (range > 0.0f)
		_range = range;

	// Set up renderer
	//Renderer.Initialize()

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
#include "DungeonKey.h"
#include "Engine_Core.h"

DungeonKey::DungeonKey()
{
	_itemType = ITEM_TYPES::DEFAULT_NONE;
	_inInventory = false;

	// Default hitbox
	hitBox.Initialize(0, 0, 0, 0);
}


DungeonKey::~DungeonKey()
{

}


void DungeonKey::Initialize(float posX, float posY, float rotationInRadians)
{
	_itemType = ITEM_TYPES::DUNGEON_KEY;

	// Set up renderer
	Renderer.Initialize(1.0f, 1.0f, 16, 16, 13, 50, 50, 0, 0, rotationInRadians, posX, posY, "items.png");

	// Initialize hitbox
	hitBox.Initialize(posX, posY, Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());
}


void DungeonKey::Update(float deltaTime)
{

}


void DungeonKey::HandleEvent(IEvent *e)
{

}


void DungeonKey::Render()
{
	if (!_inInventory)
		Renderer.Render();
}
#include "Inventory.h"
#include "Engine_Core.h"

Inventory::Inventory()
{

}


Inventory::~Inventory()
{

}


void Inventory::AddItem(IGameObject* obj)
{
	if (obj != nullptr)
		_items[obj->ID] = obj;
	else
		debug << "\tFailed to add item to inventory, ID = " << obj->ID << std::endl;
}


void Inventory::RemoveItem(unsigned int ID)
{

}


void Inventory::PurgeInventory()
{

}
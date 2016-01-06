#include "Inventory.h"
#include "Engine_Core.h"

Inventory::Inventory()
{
	_maxInventorySize = 5;
}


Inventory::~Inventory()
{
	if (_items.size() > 0)
		PurgeInventory();
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
	// Erase the item from the map
	_items.erase(ID);
}


void Inventory::PurgeInventory()
{
	// Erase all items in inventory
	std::map<unsigned int, IGameObject*>::iterator itemIt;
	for (itemIt = _items.begin(); itemIt != _items.end();)
	{
		itemIt = _items.erase(itemIt);
	}
}


/////////////////////////
// Accessors / Mutators
/////////////////////////
unsigned int Inventory::GetNumItems()
{
	int numItems = _items.size();
	if (numItems >= 0)
		return numItems;
	else
		return 0;
}


unsigned int Inventory::GetInventoryMax()
{
	if (_maxInventorySize >= 0)
		return _maxInventorySize;
	else
		return 0;
}


void Inventory::SetInventoryMax(unsigned int maxItems)
{
	_maxInventorySize = maxItems;
}
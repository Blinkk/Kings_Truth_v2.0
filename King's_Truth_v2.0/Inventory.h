#ifndef INVENTORY_H
#define INVENTORY_H
#include "IGameObject.h"
#include <map>
using namespace Smoke;

//////////////////////////////////////////////
// Only one inventory should ever be created
//////////////////////////////////////////////
class Inventory
{
private:
	std::map<unsigned int, IGameObject*> _items;
	unsigned int _maxInventorySize;

	Inventory();

public:
	static Inventory& GetInstance()
	{
		Inventory *pInstance = nullptr;

		if (pInstance == nullptr)
			pInstance = new Inventory();

		return (*pInstance);
	}

	~Inventory();

	void AddItem(IGameObject* obj);
	void RemoveItem(unsigned int objectID);
	void PurgeInventory();
};

#endif
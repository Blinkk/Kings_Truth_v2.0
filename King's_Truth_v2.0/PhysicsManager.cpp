#include "Engine_Core.h"

namespace Smoke
{
	PhysicsManager::PhysicsManager()
	{
		// Set default values
		_collisionTree = nullptr;
	}


	PhysicsManager::~PhysicsManager()
	{
		
	}


	bool PhysicsManager::Initialize()
	{
		// Create a boundary for the node to encapsulate (ie. Entire game screen)
		RECT nodeBounds = { 0, 0, SCREENW, SCREENH };

		// Initialize the collision tree
		_collisionTree = new QuadTree(0, nodeBounds);

		if (!_collisionTree)
		{
			debug << "\tFailed to initialize PhysicsManager" << std::endl;
			return false;
		}

		return true;
	}


	void PhysicsManager::Update(float deltaTime, std::vector<IGameObject*> gameObjects)
	{
		// Insert all objects' colliders into the tree
		std::vector<IGameObject*>::iterator goIt;
		for (goIt = gameObjects.begin(); goIt != gameObjects.end(); ++goIt)
		{
			// Check tags
			if ((*goIt)->tag == "Player" || (*goIt)->tag == "Enemy")
			{
				IEntity* pTemp = nullptr;
				pTemp = dynamic_cast<IEntity*>((*goIt));

				// Add collider to tree
				if (pTemp)
					_collisionTree->Insert(pTemp->hitBox);
				else
					debug << "\tFailed to insert collider into tree because casted pointer is null" << std::endl;
			}
			else if ((*goIt)->tag == "Item" || (*goIt)->tag == "StaticObject")
			{
				IItem* pTemp = nullptr;
				pTemp = dynamic_cast<IItem*>((*goIt));

				// Add collider to tree
				if (pTemp)
					_collisionTree->Insert(pTemp->hitBox);
				else
					debug << "\tFailed to insert collider into tree because casted pointer is null" << std::endl;
			}
		}
	}


	bool PhysicsManager::CheckCollision(Collider m_Object, Collider c_Object)
	{
		
	}


	void PhysicsManager::Shutdown()
	{
		// Deallocate memory
		if (_collisionTree != nullptr)
		{
			delete _collisionTree;
			_collisionTree = nullptr;
		}
	}
}
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


	void PhysicsManager::Update(float deltaTime, std::vector<IGameObject*> objects)
	{
		// Load all object's colliders into QuadTree
		_collisionTree->Clear();
		for (int i = 0; i < objects.size(); ++i)
		{
			_collisionTree->Insert(objects.at(i));
		}

		/*
			Go through each object, determine the objects it could possibly
			collide with and then check for collision
		*/
		std::vector<IGameObject*> collidableObjects;
		for (int i = 0; i < objects.size(); ++i)
		{
			// Clear the temp vector
			collidableObjects.clear();

			// Store all objects that object being checked can collide with
			_collisionTree->Retrieve(collidableObjects, objects.at(i));

			// Check collision against each collidable
			for (int j = 0; j < collidableObjects.size(); ++j)
			{
				// Check for collision
				if (CheckCollision(objects.at(i), collidableObjects.at(j)))
				{
					// Dispatch a collision event...
				}
			}
		}
	}


	bool PhysicsManager::CheckCollision(IGameObject* m_Object, IGameObject* c_Object)
	{
		// Return variable
		bool collisionOccurred = false;

		// Temp RECT to store collision area
		RECT collisionArea;

		// Store colliders of each object
		Collider collider1;
		Collider collider2;

		#pragma region CastObjects
		// Cast m_Object to correct type to access its collider
		if (m_Object->tag == "Player")
		{
			Player *pTemp = dynamic_cast<Player*>(m_Object);
			if (pTemp)
			{
				collider1 = pTemp->GetHitbox();
			}
		}
		else if (m_Object->tag == "Item")
		{
			IItem *pTemp = dynamic_cast<IItem*>(m_Object);
			if (pTemp)
			{
				collider1 = pTemp->hitBox;
			}
		}

		// Cast c_Object to correct type to access its collider
		if (c_Object->tag == "Player")
		{
			Player *pTemp = dynamic_cast<Player*>(c_Object);
			if (pTemp)
			{
				collider2 = pTemp->GetHitbox();
			}
		}
		else if (c_Object->tag == "Item")
		{
			IItem *pTemp = dynamic_cast<IItem*>(c_Object);
			if (pTemp)
			{
				collider2 = pTemp->hitBox;
			}
		}
#pragma endregion

		// Check intersection of m_Object collider to c_Object collider
		if (IntersectRect(&collisionArea, &collider1.GetBoundingBox(), &collider2.GetBoundingBox()))
		{
			collisionOccurred = true;
		}

		return collisionOccurred;
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
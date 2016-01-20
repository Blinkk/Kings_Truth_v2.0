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
	}


	void PhysicsManager::Update(float deltaTime, std::vector<Collider> colliders)
	{
		// Load all object's colliders into QuadTree
		_collisionTree->Clear();
		for (int i = 0; i < colliders.size(); ++i)
		{
			_collisionTree->Insert(colliders.at(i));
		}

		/*
			Go through each object, determine the objects it could possibly
			collide with and then check for collision
		*/
		std::vector<Collider> collidableObjects;
		for (int i = 0; i < colliders.size(); ++i)
		{
			// Clear the temp vector
			collidableObjects.clear();

			// Store all objects that object being checked can collide with
			_collisionTree->Retrieve(collidableObjects, colliders.at(i));

			// Check collision against each collidable
			for (int j = 0; j < collidableObjects.size(); ++j)
			{
				// Check for collision
				if (CheckCollision(colliders.at(i), collidableObjects.at(j)))
				{
					// Dispatch a collision event...
				}
			}
		}
	}


	bool PhysicsManager::CheckCollision(Collider m_Object, Collider c_Object)
	{
		// Return variable
		bool collisionOccurred = false;

		// Temp RECT to store collision area
		RECT collisionArea;

		// Check top of m_Object to bottom of c_Object
		if (IntersectRect(&collisionArea, &m_Object.GetBoundingBox(), &c_Object.GetBoundingBox()))
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
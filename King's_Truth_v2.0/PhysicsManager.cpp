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
		#pragma region OldCode
		//// Load all object's colliders into QuadTree
		//std::vector<IGameObject*>::iterator goIt;
		//_collisionTree->Clear();
		//for (goIt = objects.begin(); goIt != objects.end(); ++goIt)
		//{
		//	// Cast objects to determine type, insert their colliders into tree
		//	if ((*goIt)->tag == "Player")
		//	{
		//		Player *pTemp = dynamic_cast<Player*>((*goIt));
		//		if (pTemp)
		//		{
		//			Collider collider = pTemp->GetHitbox();
		//			_collisionTree->Insert(collider);
		//		}
		//	}
		//	else if ((*goIt)->tag == "Item")
		//	{
		//		IItem *pTemp = dynamic_cast<IItem*>((*goIt));
		//		if (pTemp)
		//		{
		//			Collider collider = pTemp->hitBox;
		//			_collisionTree->Insert(collider);
		//		}
		//	}
		//}
		//
		///*
		//	Go through each object, determine the objects it could possibly
		//	collide with and then check for collision
		//*/
		//std::vector<Collider> collidableObjects;
		//std::vector<Collider>::iterator colIt;
		//for (goIt = objects.begin(); goIt != objects.end(); ++goIt)
		//{
		//	// Clear the temp vector
		//	collidableObjects.clear();
		//
		//	// Cast objects to determine type, insert their colliders into tree
		//	if ((*goIt)->tag == "Player")
		//	{
		//		Player *pTemp = dynamic_cast<Player*>((*goIt));
		//		if (pTemp)
		//		{
		//			Collider collider = pTemp->GetHitbox();
		//
		//			// Store all objects that object being checked can collide with
		//			_collisionTree->Retrieve(collidableObjects, collider);
		//
		//			// Check collision against each collidable
		//			for (colIt = collidableObjects.begin(); colIt != collidableObjects.end(); ++colIt)
		//			{
		//				// Check for collision
		//				if (CheckCollision(collider, (*colIt)))
		//				{
		//					// Dispatch a collision event...
		//				}
		//			}
		//		}
		//	}
		//	else if ((*goIt)->tag == "Item")
		//	{
		//		IItem *pTemp = dynamic_cast<IItem*>((*goIt));
		//		if (pTemp)
		//		{
		//			Collider collider = pTemp->hitBox;
		//
		//			// Store all objects that object being checked can collide with
		//			_collisionTree->Retrieve(collidableObjects, collider);
		//
		//			// Check collision against each collidable
		//			for (colIt = collidableObjects.begin(); colIt != collidableObjects.end(); ++colIt)
		//			{
		//				// Check for collision
		//				if (CheckCollision(collider, (*colIt)))
		//				{
		//					// Dispatch a collision event...
		//				}
		//			}
		//		}
		//	}		
		//}
#pragma endregion
	}


	bool PhysicsManager::CheckCollision(Collider m_Object, Collider c_Object)
	{
		// Return variable
		bool collisionOccurred = false;

		// Temp RECT to store collision area
		RECT collisionArea;

		//		#pragma region CastObjects
//		// Cast m_Object to correct type to access its collider
//		if (m_Object->tag == "Player")
//		{
//			Player *pTemp = dynamic_cast<Player*>(m_Object);
//			if (pTemp)
//			{
//				collider1 = pTemp->GetHitbox();
//			}
//		}
//		else if (m_Object->tag == "Item")
//		{
//			IItem *pTemp = dynamic_cast<IItem*>(m_Object);
//			if (pTemp)
//			{
//				collider1 = pTemp->hitBox;
//			}
//		}
//
//		// Cast c_Object to correct type to access its collider
//		if (c_Object->tag == "Player")
//		{
//			Player *pTemp = dynamic_cast<Player*>(c_Object);
//			if (pTemp)
//			{
//				collider2 = pTemp->GetHitbox();
//			}
//		}
//		else if (c_Object->tag == "Item")
//		{
//			IItem *pTemp = dynamic_cast<IItem*>(c_Object);
//			if (pTemp)
//			{
//				collider2 = pTemp->hitBox;
//			}
//		}
//#pragma endregion

		// Check intersection of m_Object collider to c_Object collider
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
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "QuadTree.h"
#include "IGameObject.h"

namespace Smoke
{
	class PhysicsManager
	{
	private:
		QuadTree *_collisionTree;		// Base of collision QuadTree

		PhysicsManager();

	public:
		static PhysicsManager& GetInstance()
		{
			static PhysicsManager* pInstance = nullptr;

			if (!pInstance)
			{
				pInstance = new PhysicsManager();
			}

			return (*pInstance);
		}
		~PhysicsManager();

		bool Initialize();
		void Update(float deltaTime, std::vector<IGameObject*> gameObjects);
		void Shutdown();

		// Checks collision between (main object & collidable object)
		bool CheckCollision(Collider m_Object, Collider c_Object);
	};
}

#endif
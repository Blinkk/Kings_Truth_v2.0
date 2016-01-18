#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include "QuadTree.h"

namespace Smoke
{
	class PhysicsManager
	{
	private:
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
		void Update(float deltaTime, std::vector<Collider>);
		void Shutdown();
	};
}

#endif
#ifndef QUADTREE_H
#define QUADTREE_H
#include "IGameObject.h"
#include "stdafx.h"
#include <list>

namespace Smoke
{
	class QuadTree
	{
	private:
		const unsigned int MAX_OBJECTS = 10;		// Max num of objects per node level
		const unsigned int MAX_NODE_LEVEL = 5;		// Max num of node levels

		unsigned int _currentNodeLevel;				// Current node level
		std::vector<IGameObject*> _objects;			// Vector of object colliders to check
		std::vector<IGameObject*>::iterator _cIt;	// Collider vector iterator
		QuadTree** _nodes;							// Pointer to array of node pointers
		RECT _nodeBounds;							// Bounds that node encapsulates

		/////////////////////
		// Utility Functions
		/////////////////////
		int GetIndex(IGameObject* object);			// Determines which node to place object in

	public:
		QuadTree(unsigned int nodeLevel, RECT nodeBounds);
		~QuadTree();

		void Clear();								// Erase all elements in entire tree
		void Split();								// Split node into smaller sub-sections (ie. expand the tree)
		void Insert(IGameObject* object);			// Insert object into tree 

		// Retrieves all objects that are likely to collide with the object passed to it
		std::vector<IGameObject*> Retrieve(std::vector<IGameObject*> returnObjects, IGameObject* object);
	};
}

#endif
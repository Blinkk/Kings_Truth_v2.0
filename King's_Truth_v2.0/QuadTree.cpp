#include "Engine_Core.h"

namespace Smoke
{
	QuadTree::QuadTree(unsigned int nodeLevel, RECT nodeBounds)
	{
		// Set initial values
		_currentNodeLevel = nodeLevel;
		_nodeBounds = nodeBounds;

		// Reset index
		_currentIndex = 0;

		// Initialize array
		_objects = new Collider[MAX_OBJECTS];

		// Initialize sub-nodes to nullptr
		for (int i = 0; i < 4; ++i)
		{
			_nodes[i] = nullptr;
		}
	}


	QuadTree::~QuadTree()
	{
		// Deallocate memory
		this->Clear();
	}


	void QuadTree::Clear()
	{
		/*
			Note: We only delete the pointer to the array, not the pointers
			that it holds because there are still needed elsewhere
		*/
		if (_objects)
		{
			delete[] _objects;
			_objects = nullptr;
		}

		// Call each node's Clear() method and delete nodes
		for (int i = 0; i < 4; ++i)
		{
			if (_nodes[i] != nullptr)
			{
				_nodes[i]->Clear();
		
				// Delete the node
				delete _nodes[i];
				_nodes[i] = nullptr;
			}
		}
	}


	void QuadTree::Split()
	{
		// Calculate split dimensions
		int subWidth = (int)((_nodeBounds.right - _nodeBounds.left) / 2);
		int subHeight = (int)((_nodeBounds.bottom - _nodeBounds.top) / 2);
		int x = (int)_nodeBounds.left;
		int y = (int)_nodeBounds.top;

		// Set up RECTS
		RECT r1 = { x + subWidth, y, subWidth, subHeight };
		RECT r2 = { x, y, subWidth, subHeight };
		RECT r3 = { x, y + subHeight, subWidth, subHeight };
		RECT r4 = { x + subWidth, y + subHeight, subWidth, subHeight };

		// Create the new nodes with their given nodeLevel and bounds
		_nodes[0] = new QuadTree(_currentNodeLevel + 1, r1);
		_nodes[1] = new QuadTree(_currentNodeLevel + 1, r2);
		_nodes[2] = new QuadTree(_currentNodeLevel + 1, r3);
		_nodes[3] = new QuadTree(_currentNodeLevel + 1, r4);
	}


	void QuadTree::Insert(Collider collider)
	{
		/*
			If the nodes at this level already contain colliders,
			determine the index that this collider should reside in
			and call that node's Insert() method. This continues until
			an appropriate node level is reached.
		*/
		if (_nodes[0] != nullptr) 
		{
			int index = GetIndex(collider);
			if (index != -1) 
			{
				_nodes[index]->Insert(collider);
				return;
			}
		}

		// Once appropriate node level is reached, insert the collider into the array for this node
		_objects[_currentIndex] = collider;

		// Increment index
		++_currentIndex;

		/*
			If the MAX_OBJECTS for this node has been reached, but the 
			MAX_NODE_LEVEL has not, split the node and distribute colliders
			into the new nodes.
		*/
		if ((_currentIndex + 1) > MAX_OBJECTS && _currentNodeLevel < MAX_NODE_LEVEL) 
		{
			// Ensure nodes are NULL, then call Split() method
			if (_nodes[0] == nullptr) 
			{
				Split();
			}

			int i = 0;
			while (i < (_currentIndex + 1)) 
			{
				int index = GetIndex(_objects[i]);
				if (index != -1) 
				{
					// Insert the collider into new node at specified index
					_nodes[index]->Insert(_objects[i]);

					// Remove the element from the array
					std::remove(_objects[0], _objects[_currentIndex + 1], _objects[i]);
				}
				else 
				{
					i++;
				}
			}
		}
	}



	void QuadTree::Retrieve(std::vector<Collider> &returnObjects, Collider collider)
	{
		int index = GetIndex(collider);
		if (index != -1 && _nodes[0] != nullptr) 
		{
			_nodes[index]->Retrieve(returnObjects, collider);
		}

		// Get all objects that the collider could collide with
		for (int i = 0; i < (_currentIndex + 1); ++i)
		{
			returnObjects.push_back(_objects[i]);
		}
	}


	/////////////////////
	// Utility Functions
	/////////////////////
	int QuadTree::GetIndex(Collider collider)
	{
		// Determine index
		int index = -1;
		double verticalMidpoint = _nodeBounds.left + ((_nodeBounds.right - _nodeBounds.left) / 2);
		double horizontalMidpoint = _nodeBounds.top + ((_nodeBounds.bottom - _nodeBounds.top) / 2);

		// Object can completely fit within the top quadrants
		bool topQuadrant = (collider.GetBoundingBox().top < horizontalMidpoint 
			&& collider.GetBoundingBox().top + (collider.GetBoundingBox().bottom - collider.GetBoundingBox().top) < horizontalMidpoint);
		// Object can completely fit within the bottom quadrants
		bool bottomQuadrant = (collider.GetBoundingBox().top > horizontalMidpoint);

		// Object can completely fit within the left quadrants
		if (collider.GetBoundingBox().left < verticalMidpoint 
			&& collider.GetBoundingBox().left + (collider.GetBoundingBox().right - collider.GetBoundingBox().left) < verticalMidpoint) 
		{
			if (topQuadrant) 
			{
				index = 1;
			}
			else if (bottomQuadrant) 
			{
				index = 2;
			}
		}
		// Object can completely fit within the right quadrants
		else if (collider.GetBoundingBox().left > verticalMidpoint) 
		{
			if (topQuadrant) 
			{
				index = 0;
			}
			else if (bottomQuadrant) 
			{
				index = 3;
			}
		}

		return index;
	}
}
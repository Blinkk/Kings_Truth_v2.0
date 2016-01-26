/*
* Copyright (c) 2008, Power of Two Games LLC
* All rights reserved.
*/
/*
	Slightly modified handle system based off of a system developed by the
	company listed above. 
*/
#ifndef HANDLE_H
#define HANDLE_H

typedef unsigned int uint32;

namespace Smoke
{
	struct Handle
	{
		// Default constructor
		Handle() : index(0), counter(0), type(0)
		{}

		// Overloaded constructor (n_Variable = "New" variable)
		Handle(uint32 n_index, uint32 n_counter, uint32 n_type)
			: index(n_index), counter(n_counter), type(n_type)
		{}

		// Function to return specialized uint32
		inline operator uint32() const;

		uint32 index : 12;			// Index of handle
		uint32 counter : 15;		// Tracks number of time an index is used
		uint32 type : 5;			// Type of object/data in handle
	};


	Handle::operator uint32() const
	{
		return type << 27 | counter << 12 | index;
	}
}

#endif
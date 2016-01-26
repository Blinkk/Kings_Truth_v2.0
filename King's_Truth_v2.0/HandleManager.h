/*
* Copyright (c) 2008, Power of Two Games LLC
* All rights reserved.
*/
/*
	Slightly modified handle system based off of a system developed by the
	company listed above.
*/
#ifndef HANDLEMANAGER_H
#define HANDLEMANAGER_H
#include "Handle.h"

namespace Smoke
{
	class HandleManager
	{
	public:
		enum { MaxEntries = 4096 };

		HandleManager();

		void Reset();
		Handle Add(void* p, uint32 type);
		void Update(Handle handle, void* p);
		void Remove(Handle handle);

		void* Get(Handle handle) const;
		bool Get(Handle handle, void*& out) const;
		template< typename T > bool GetAs(Handle handle, T& out) const;

		int GetCount() const;

	private:
		// Handle entry to store 
		struct HandleEntry
		{
			HandleEntry();
			explicit HandleEntry(uint32 nextFreeIndex);

			uint32 nextFreeIndex : 12;
			uint32 counter : 15;
			uint32 active : 1;
			uint32 endOfList : 1;
			void* entry;
		};

		HandleEntry _entries[MaxEntries];

		int _activeEntryCount;
		uint32 _firstFreeEntry;
	};


	template< typename T >
	inline bool HandleManager::GetAs(Handle handle, T& out) const
	{
		void* outAsVoid;
		const bool rv = Get(handle, outAsVoid);
		out = union_cast< T >(outAsVoid);

		return rv;
	}

}

#endif
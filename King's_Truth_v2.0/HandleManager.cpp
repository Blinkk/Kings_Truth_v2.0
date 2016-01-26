/*
* Copyright (c) 2008, Power of Two Games LLC
* All rights reserved.
*/
/*
	Slightly modified handle system based off of a system developed by the
	company listed above.
*/
#include "Engine_Core.h"
#include "HandleManager.h"
#include <cstddef>


namespace Smoke
{
	HandleManager::HandleEntry::HandleEntry()
		: nextFreeIndex(0)
		, counter(1)
		, active(0)
		, endOfList(0)
		, entry(NULL)
	{}

	HandleManager::HandleEntry::HandleEntry(uint32 nextFreeIndex)
		: nextFreeIndex(nextFreeIndex)
		, counter(1)
		, active(0)
		, endOfList(0)
		, entry(NULL)
	{}



	HandleManager::HandleManager()
	{
		Reset();
	}


	void HandleManager::Reset()
	{
		_activeEntryCount = 0;
		_firstFreeEntry = 0;

		for (int i = 0; i < MaxEntries - 1; ++i)
			_entries[i] = HandleEntry(i + 1);
		_entries[MaxEntries - 1] = HandleEntry();
		_entries[MaxEntries - 1].endOfList = true;
	}


	Handle HandleManager::Add(void* p, uint32 type)
	{
		if (_activeEntryCount >= MaxEntries - 1)
		{
			debug << "\tMax handle count has been reached, no handle could be added" << std::endl;
			return;
		}
		if (type < 0 && type > 31)
		{
			debug << "\tType out of range (0-31), no handle could be added" << std::endl;
			return;
		}

		// Get new index based on next free entry in HandleEntry array
		const int newIndex = _firstFreeEntry;
		if (newIndex >= MaxEntries)
		{
			debug << "\tNew index >= MaxEntries, no handle could be added" << std::endl;
			return;
		}
		if (!_entries[newIndex].active == false)
		{
			debug << "\tEntry at new index is already active, no handle could be added" << std::endl;
			return;
		}
		if (_entries[newIndex].endOfList)
		{
			debug << "\tEntry at new index is end of list, no handle could be added" << std::endl;
			return;
		}

		//////////////////////////////////////////////
		// Set up new handle, reset m_firstFreeEntry
		//////////////////////////////////////////////
		_firstFreeEntry = _entries[newIndex].nextFreeIndex;
		_entries[newIndex].nextFreeIndex = 0;
		_entries[newIndex].counter = _entries[newIndex].counter + 1;
		if (_entries[newIndex].counter == 0)
			_entries[newIndex].counter = 1;
		_entries[newIndex].active = true;
		_entries[newIndex].entry = p;

		++_activeEntryCount;

		return Handle(newIndex, _entries[newIndex].counter, type);
	}


	void HandleManager::Update(Handle handle, void* p)
	{
		// Get index of handle and check that it is valid
		const int index = handle.index;
		if (_entries[index].counter != handle.counter)
		{
			debug << "\tCounters are not equal, handle could not be updated because the entry in this index is invalid" << std::endl;
			return;
		}
		if (_entries[index].active != true)
		{
			debug << "\tThis handle is inactive, handle could not be updated because the entry in this index is invalid" << std::endl;
			return;
		}

		// Update the pointer that this entry holds
		_entries[index].entry = p;
	}


	void HandleManager::Remove(const Handle handle)
	{
		const uint32 index = handle.index;
		if (_entries[index].counter != handle.counter)
		{
			debug << "\tCounters are not equal, handle could not be removed because it is invalid" << std::endl;
			return;
		}
		if (_entries[index].active != true)
		{
			debug << "\tThis handle is inactive, handle could not be removed because it is invalid" << std::endl;
			return;
		}

		// Set handle entry values to default, and next index to the next free entry
		_entries[index].nextFreeIndex = _firstFreeEntry;
		_entries[index].active = 0;
		_firstFreeEntry = index;

		--_activeEntryCount;
	}


	void* HandleManager::Get(Handle handle) const
	{
		void* p = NULL;
		if (!Get(handle, p))
			return NULL;
		return p;
	}


	bool HandleManager::Get(const Handle handle, void*& out) const
	{
		const int index = handle.m_index;
		if (m_entries[index].m_counter != handle.m_counter ||
			m_entries[index].m_active == false)
			return false;

		out = m_entries[index].m_entry;
		return true;
	}


	int HandleManager::GetCount() const
	{
		return m_activeEntryCount;
	}


}

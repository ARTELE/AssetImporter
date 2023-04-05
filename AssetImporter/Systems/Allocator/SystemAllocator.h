#pragma once
#include "BaseAllocator.h"
#include <unordered_map>
#include <iostream>
#include <Modules/Log/Log.h>
class SystemAllocator : public BaseAllocator
{
	std::unordered_map<char*, std::pair<std::string, uint32_t>> memoryAddresses;
public:

	SystemAllocator() {}
	
	template<typename T>
	T* AllocateArray(size_t size, std::string tag = "no_name")
	{
		T* tempMemory = new T[size];
		memoryAddresses.insert(std::make_pair((char*)tempMemory, std::make_pair(tag, size * sizeof(T))));
		return tempMemory;
	}

	template<typename T>
	T* Allocate(std::string tag = "no_name")
	{
		T* tempMemory = new T;
		memoryAddresses.insert(std::make_pair((char*)tempMemory, std::make_pair(tag, sizeof(T))));
		return tempMemory;
	}

	template<typename T>
	void Deallocate(T* address)
	{
		auto iter = memoryAddresses.find(address);
		if(iter != memoryAddresses.end())
		{
			memoryAddresses.erase(iter);
			delete[] address;
		}
	}

	void DeallocateAll()
	{
		for (auto& memory : memoryAddresses)
		{
			delete[] memory.first;
			std::string msg = "Memory leak. Tag:";
			msg += memory.second.first;
			msg += " Size:";
			msg += std::to_string(memory.second.second);
			msg += " Bytes. SystemAllocator will auto deallocate.";
			WarningMessage(msg);
		}

		memoryAddresses.clear();
	}

	~SystemAllocator() 
	{
		if (memoryAddresses.size() > 0)
		{
			//todo: log warning
			DeallocateAll();
		}
	}
};
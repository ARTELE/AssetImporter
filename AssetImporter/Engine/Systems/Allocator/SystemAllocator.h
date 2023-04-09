#pragma once
#include "BaseAllocator.h"
#include <unordered_map>
#include <iostream>
#include <Engine/Modules/Log/Log.h>
class SystemAllocator : public BaseAllocator
{
	std::unordered_map<char*, std::pair<std::string, uint32_t>> memoryAddresses;
	bool autoDecllocate = true;
	void DeallocateAll()
	{
		for (auto& memory : memoryAddresses)
		{
			delete[] memory.first;
			std::string msg = "Memory leak. ";
			msg += memory.second.first;
			msg += " Size:";
			msg += std::to_string(memory.second.second);
			msg += " Bytes. SystemAllocator will auto deallocate.";
			WarningMessage(msg);
		}

		memoryAddresses.clear();
	}
public:

	SystemAllocator() { label = "SystemAllocator"; }
	SystemAllocator(bool autoDecllocate) : autoDecllocate(autoDecllocate) { label = "SystemAllocator"; }
	SystemAllocator(std::string label) : BaseAllocator(label) {}

	template<typename T>
	T* Allocate(size_t size = 1, std::string tag = "no_name")
	{
		T* tempMemory = new T[size];
		memoryAddresses.insert(std::make_pair((char*)tempMemory, std::make_pair(std::string(label + "-" + tag), size)));
		return tempMemory;
	}

	template<typename T>
	void Deallocate(T* address)
	{
		auto iter = memoryAddresses.find((char*)address);
		if (iter != memoryAddresses.end())
		{
			memoryAddresses.erase(iter);
			delete[] address;
		}
	}

	~SystemAllocator() 
	{
		if (memoryAddresses.size() > 0 && autoDecllocate)
		{
			DeallocateAll();
		}
	}
};
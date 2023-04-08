#pragma once
#include "BaseAllocator.h"
#include <unordered_map>
#include <iostream>
#include <Modules/Log/Log.h>
class SystemAllocator : public BaseAllocator
{
	std::unordered_map<char*, std::pair<std::string, uint32_t>> memoryAddresses;
	virtual char* InternalAllocate(size_t size, std::string tag = "no_name")
	{
		char* tempMemory = new char[size];
		memoryAddresses.insert(std::make_pair(tempMemory, std::make_pair(std::string(label + "-" + tag), size)));
		return tempMemory;
	}

	virtual void InternalDeallocate(char* address)
	{
		auto iter = memoryAddresses.find(address);
		if (iter != memoryAddresses.end())
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
	SystemAllocator(std::string label) : BaseAllocator(label) {}

	~SystemAllocator() 
	{
		if (memoryAddresses.size() > 0)
		{
			DeallocateAll();
		}
	}
};
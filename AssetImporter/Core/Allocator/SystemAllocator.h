#pragma once
#include "BaseAllocator.h"
#include <unordered_map>
#include <iostream>
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
			std::cout << "Warning: Memory leak. Tag:" << memory.second.first << " Size:" << memory.second.second << " Bytes. SystemAllocator will auto deallocate." << std::endl;
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
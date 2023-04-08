#pragma once
#include <string>
class BaseAllocator
{
protected:
	std::string label;
	virtual char* InternalAllocate(size_t size, std::string tag = "no_name") = 0;
	virtual void InternalDeallocate(char* address) = 0;
public:
	BaseAllocator(){}
	BaseAllocator(std::string label) : label(label) {}

	template<typename T>
	T* Allocate(size_t size, std::string tag = "no_name")
	{
		return (T*)InternalAllocate(size * sizeof(T), tag);
	}
	
	template<typename T>
	void Deallocate(T* address)
	{
		InternalDeallocate((char*)address);
	}

};
#pragma once
#include <string>
class BaseAllocator
{
protected:
	std::string label;
public:
	BaseAllocator(){}
	BaseAllocator(std::string label) : label(label) {}
};
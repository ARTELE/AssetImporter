#pragma once
#include <string>
#include <vector>
#include<concepts>
#include <Engine/Systems/Allocator/SystemAllocator.h>
using namespace std;

#define SERIALIZE(x) serializer.Serialize(x, #x)
#define SERIALIZE_PTR(x, size) serializer.SerializePtr(x, size, #x)
#define SERIALIZE_BASE(x) Serialize(x, #x)
#define SERIALIZE_ARRAY_ELEMENT(x, i) serializer.Serialize(x[i], std::string(#x) + "[" + std::to_string(i) + "]")

template<typename T>
concept BaseType = std::is_integral_v<T> || std::is_floating_point_v<T>;

template<typename T>
class SerializeTraits
{
public:
	template<typename SerializeFunction>
	static void Serialize(T& data, SerializeFunction& serialize)
	{
		data.Serialize(serialize);
	}
};

class SerializeBase
{
protected:
	std::vector<std::string> nameStack;
	SystemAllocator allocator;
	BaseAllocator* userAllocator = nullptr;

	string GetName()
	{
		string valueName = "";
		for (int i = 0; i < nameStack.size(); i++)
		{
			valueName += nameStack[i];
			if (i != nameStack.size() - 1)
			{
				valueName += ".";
			}
		}
		return valueName;
	}

public:

	void SetUserAllocator(BaseAllocator* allocator)
	{
		userAllocator = allocator;
	}
};

enum ResourceType
{
	NONE = 0,
	PICTURE = 1,
};

struct ValueInfo
{
	ValueInfo() {}
	ValueInfo(const char* name, uint32_t offset, uint32_t dataSize)
		: offset(offset)
		, dataSize(dataSize)
	{
		nameStrLength = strlen(name);
		int alignLength = nameStrLength + (4 - (nameStrLength % 4));
		this->name = new char[alignLength];
		memset(this->name, 0, alignLength);
		memcpy(this->name, name, nameStrLength);
		nameStrLength = alignLength;
	}

	ValueInfo(const ValueInfo& valueInfo)
		: nameStrLength(valueInfo.nameStrLength)
		, offset(valueInfo.offset)
		, dataSize(valueInfo.dataSize)
	{
		if (name != nullptr)
		{
			delete[] name;
		}
		name = nullptr;
		name = new char[nameStrLength + 1];
		memset(this->name, 0, nameStrLength + 1);
		memcpy(name, valueInfo.name, nameStrLength);
	}

	uint32_t nameStrLength = 0;
	char* name = nullptr;
	uint32_t offset = 0;
	uint32_t dataSize = 0;

	static uint32_t ReadValueInfo(char* buffer, uint32_t offset, ValueInfo& valueInfo)
	{
		if (buffer == nullptr)
		{
			return offset;
		}
		uint32_t bufferOffset = offset;

		memcpy(&valueInfo.nameStrLength, buffer + bufferOffset, sizeof(uint32_t));
		bufferOffset += sizeof(uint32_t);

		if (valueInfo.name != nullptr)
		{
			delete[] valueInfo.name;
			valueInfo.name = nullptr;
		}
		valueInfo.name = new char[valueInfo.nameStrLength];
		memcpy(valueInfo.name, buffer + bufferOffset, valueInfo.nameStrLength);
		bufferOffset += valueInfo.nameStrLength;

		memcpy(&valueInfo.offset, buffer + bufferOffset, sizeof(uint32_t));
		bufferOffset += sizeof(uint32_t);

		memcpy(&valueInfo.dataSize, buffer + bufferOffset, sizeof(uint32_t));
		bufferOffset += sizeof(uint32_t);

		return bufferOffset;
	}

	static uint32_t WriteValueInfo(char* buffer, uint32_t offset, const ValueInfo& valueInfo)
	{
		if (buffer == nullptr)
		{
			return 0;
		}

		uint32_t bufferOffset = offset;
		memcpy(buffer + bufferOffset, &valueInfo.nameStrLength, sizeof(uint32_t));
		bufferOffset += sizeof(uint32_t);

		memcpy(buffer + bufferOffset, valueInfo.name, valueInfo.nameStrLength);
		bufferOffset += valueInfo.nameStrLength;

		memcpy(buffer + bufferOffset, &valueInfo.offset, sizeof(uint32_t));
		bufferOffset += sizeof(uint32_t);

		memcpy(buffer + bufferOffset, &valueInfo.dataSize, sizeof(uint32_t));
		bufferOffset += sizeof(uint32_t);

		return bufferOffset;
	}

	~ValueInfo()
	{
		if (name != nullptr)
		{
			delete[] name;
		}
		name = nullptr;
	}
};
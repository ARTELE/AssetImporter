#pragma once
#include "Serialization.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <assert.h>
#include <Modules/Log/Log.h>
#include <Systems/Allocator/BaseAllocator.h>

struct BinaryFileMark
{
	const char name[16] = "BIN 0.1.";
	uint32_t num = 0xFAEA9971;
};

class BinaryFileRead : public SerializeBase
{
	std::ifstream file;
	std::vector<ValueInfo> valueInfos;
	uint32_t headBufferSize = 0;
	uint32_t dataBufferSize = 0;
	char* headBuffer = nullptr;
	char* dataBuffer = nullptr;
	std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> valueMap;
	SystemAllocator* userAllocator = nullptr;

public:
	BinaryFileRead() {}
	BinaryFileRead(const char* fileName)
	{
		OpenBinaryFile(fileName);
	}

	bool OpenBinaryFile(const char* fileName)
	{
		file.open(fileName, std::ios::binary | std::ios::in);
		if (file.is_open())
		{
			return true;
		}
		else
		{
			std::string msg = "Can not find file " + std::string(fileName);
			ErrorMessage(msg);

			return false;
		}
	}

	void SetUserAllocator(SystemAllocator* allocator)
	{
		userAllocator = allocator;
	}

	template<typename T>
	void Serialize(T& data, const string& name)
	{
		nameStack.push_back(name);
		SerializeTraits<T>::Serialize(data, *this);
		nameStack.pop_back();
	}

	template<typename T>
	void Serialize(T& data, const std::string& name) requires BaseType<T>
	{
		nameStack.push_back(name);

		std::string valueName = GetName();
		auto iter = valueMap.find(valueName);
		if (iter != valueMap.end())
		{
			memcpy(&data, dataBuffer + iter->second.first, iter->second.second);
		}

		nameStack.pop_back();
	}

	template<typename T>
	void SerializePtr(T* &data, uint32_t size, const string& name) requires BaseType<T>
	{
		nameStack.push_back(name);

		std::string valueName = GetName();
		auto iter = valueMap.find(valueName);
		if (iter != valueMap.end())
		{
			if (data != nullptr)
			{
				ErrorMessage(name + " serialize failed, need nullptr input.");
				return;
			}
			else
			{
				if (userAllocator == nullptr)
				{
					ErrorMessage("userAllocator is nullptr.");
					return;
				}
				else
				{
					data = userAllocator->AllocateArray<T>(iter->second.second);
				}
			}
			memcpy(data, dataBuffer + iter->second.first, iter->second.second);
		}

		nameStack.pop_back();
	}
	
	void BeginSerialize()
	{
		if (file.is_open())
		{
			BinaryFileMark mark;
			file.read((char*)&mark, sizeof(BinaryFileMark));
			file.read((char*)&headBufferSize, sizeof(uint32_t));
			file.read((char*)&dataBufferSize, sizeof(uint32_t));
			headBuffer = allocator.AllocateArray<char>(headBufferSize, "BinaryFileRead::BeginSerialize headBufferSize");
			file.read(headBuffer, headBufferSize);
			dataBuffer = allocator.AllocateArray<char>(dataBufferSize, "BinaryFileRead::BeginSerialize dataBufferSize");
			file.read(dataBuffer, dataBufferSize);

			int i = 0;
			while (i < headBufferSize)
			{
				ValueInfo valueInfo;
				i = ValueInfo::ReadValueInfo(headBuffer, i, valueInfo);
				valueMap.insert(std::make_pair(std::string(valueInfo.name), std::make_pair(valueInfo.offset, valueInfo.dataSize)));
			}
		}
	}

	void EndSerialize()
	{
		file.close();

		allocator.Deallocate(dataBuffer);
		allocator.Deallocate(headBuffer);
	}

	~BinaryFileRead()
	{
	}
};

class BinaryFileWrite : public SerializeBase
{
	std::ofstream file;
	std::vector<ValueInfo> valueInfos;
	uint32_t dataOffset = 0;
	char* dataBuffer = nullptr;
	uint32_t dataBufferSize = 1024;
	SystemAllocator* userAllocator = nullptr;

	void ExpansionBuffer()
	{
		if (dataOffset + 128 >= dataBufferSize)
		{
			dataBufferSize *= 2;
			char* newDataBuffer = allocator.AllocateArray<char>(dataBufferSize, "BinaryFileWrite::BeginSerialize dataBufferSize");
			memcpy(newDataBuffer, dataBuffer, dataOffset);
			allocator.Deallocate(dataBuffer);
			dataBuffer = newDataBuffer;
		}
	}
public:
	BinaryFileWrite() {}
	BinaryFileWrite(const char* fileName)
	{
		OpenBinaryFile(fileName);
	}

	bool OpenBinaryFile(const char* fileName)
	{
		file.open(fileName, std::ios::binary | std::ios::out);
		if (file.is_open())
		{
			return true;
		}
		else
		{
			std::string msg = "Can not find file " + std::string(fileName);
			ErrorMessage(msg);

			return false;
		}
	}

	void SetUserAllocator(SystemAllocator* allocator)
	{
		userAllocator = allocator;
	}

	template<typename T>
	void Serialize(T& data, const string& name)
	{
		nameStack.push_back(name);
		SerializeTraits<T>::Serialize(data, *this);
		nameStack.pop_back();
	}

	template<typename T>
	void Serialize(T& data, const string& name) requires BaseType<T>
	{
		nameStack.push_back(name);
		string valueName = GetName();

		memcpy(dataBuffer + dataOffset, &data, sizeof(T));
		valueInfos.push_back(ValueInfo(valueName.c_str(), dataOffset, sizeof(T)));
		dataOffset += sizeof(T);
		ExpansionBuffer();

		nameStack.pop_back();
	}

	template<typename T>
	void SerializePtr(T* &data, uint32_t size, const string& name) requires BaseType<T>
	{
		if (data == nullptr)
		{
			ErrorMessage(std::string("Serialize failed" + name + " is nullptr."));
			return;
		}

		nameStack.push_back(name);
		string valueName = GetName();

		memcpy(dataBuffer + dataOffset, data, sizeof(T) * size);
		valueInfos.push_back(ValueInfo(valueName.c_str(), dataOffset, sizeof(T) * size));
		dataOffset += sizeof(T) * size;
		ExpansionBuffer();

		nameStack.pop_back();
	}

	void BeginSerialize()
	{
		dataBuffer = allocator.AllocateArray<char>(dataBufferSize, "BinaryFileWrite::BeginSerialize dataBufferSize");
	}

	void EndSerialize()
	{
		uint32_t headBufferSize = 0;
		for (int i = 0; i < valueInfos.size(); i++)
		{
			headBufferSize += valueInfos[i].nameStrLength;
			headBufferSize += 12;
		}

		char* headBuffer = allocator.AllocateArray<char>(headBufferSize, "BinaryFileWrite::BeginSerialize headBufferSize");
		int offset = 0;
		for (int i = 0; i < valueInfos.size(); i++)
		{
			offset = ValueInfo::WriteValueInfo(headBuffer, offset, valueInfos[i]);
		}

		BinaryFileMark mark;
		file.write((const char*)&mark, sizeof(BinaryFileMark));
		file.write((const char*)&headBufferSize, sizeof(headBufferSize));
		file.write((const char*)&dataOffset, sizeof(dataOffset));
		file.write((const char*)headBuffer, headBufferSize);
		file.write((const char*)dataBuffer, dataOffset);

		allocator.Deallocate(headBuffer);

		file.close();
		
		dataOffset = 0;
		allocator.Deallocate(dataBuffer);
	}

	~BinaryFileWrite()
	{
	}
};

#define BINARY_FILE_SERIALIZE_WRITE(object, fileName) \
BinaryFileWrite write; \
if(write.OpenBinaryFile(fileName)) \
{ \
	write.BeginSerialize(); \
	object.Serialize(write); \
	write.EndSerialize(); \
}

#define BINARY_FILE_SERIALIZE_READ(object, fileName) \
BinaryFileRead read; \
if(read.OpenBinaryFile(fileName)) \
{ \
	read.BeginSerialize(); \
	object.Serialize(read); \
	read.EndSerialize(); \
}
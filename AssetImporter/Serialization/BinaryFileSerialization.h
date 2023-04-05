#pragma once
#include "Serialization.h"
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>

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

public:
	BinaryFileRead() {}
	BinaryFileRead(const char* fileName)
	{
		file.open(fileName, std::ios::binary | std::ios::in);
		if (file.is_open())
		{
			BinaryFileMark mark;
			file.read((char*)&mark, sizeof(BinaryFileMark));
			file.read((char*)&headBufferSize, sizeof(uint32_t));
			file.read((char*)&dataBufferSize, sizeof(uint32_t));
			headBuffer = allocator.AllocateArray<char>(headBufferSize);
			file.read(headBuffer, headBufferSize);
			dataBuffer = allocator.AllocateArray<char>(dataBufferSize);
			file.read(dataBuffer, dataBufferSize);

			int i = 0;
			while (i < headBufferSize)
			{	
				ValueInfo valueInfo;
				i = ValueInfo::ReadValueInfo(headBuffer, i, valueInfo);
				valueMap.insert(std::make_pair(std::string(valueInfo.name), std::make_pair(valueInfo.offset, valueInfo.dataSize)));
			}
		}
		//todo: warning log
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

	void EndSerialize()
	{
		file.close();
	}

	~BinaryFileRead()
	{
		allocator.Deallocate(dataBuffer);
		allocator.Deallocate(headBuffer);
	}
};

class BinaryFileWrite : public SerializeBase
{
	std::ofstream file;
	std::vector<ValueInfo> valueInfos;
	uint32_t dataOffset = 0;
	char* dataBuffer = nullptr;
	uint32_t dataBufferSize = 1024;
public:
	BinaryFileWrite() {}
	BinaryFileWrite(const char* fileName)
	{
		file.open(fileName, std::ios::binary | std::ios::out);
		//todo: warning log
		dataBuffer = allocator.AllocateArray<char>(dataBufferSize);
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

		if (dataOffset + 128 >= dataBufferSize)
		{
			dataBufferSize *= 2;
			char* newDataBuffer = allocator.AllocateArray<char>(dataBufferSize);
			memcpy(newDataBuffer, dataBuffer, dataOffset);
			allocator.Deallocate(dataBuffer);
			dataBuffer = newDataBuffer;
		}

		nameStack.pop_back();
	}

	void EndSerialize()
	{
		uint32_t headBufferSize = 0;
		for (int i = 0; i < valueInfos.size(); i++)
		{
			headBufferSize += valueInfos[i].nameStrLength;
			headBufferSize += 12;
		}

		char* headBuffer = allocator.AllocateArray<char>(headBufferSize);
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
	}

	~BinaryFileWrite()
	{
		allocator.Deallocate(dataBuffer);
	}
};

#define BINARY_FILE_SERIALIZE_WRITE(object, filename) \
BinaryFileWrite write(filename); \
object.Serialize(write); \
write.EndSerialize();

#define BINARY_FILE_SERIALIZE_READ(object, filename) \
BinaryFileRead read(filename); \
object.Serialize(read); \
read.EndSerialize();
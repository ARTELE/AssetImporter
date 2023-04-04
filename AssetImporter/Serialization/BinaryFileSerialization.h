#pragma once
#include "Serialization.h"
#include <vector>
#include <fstream>
//class BinaryFileRead
//{
//	
//	std::vector<std::string> nameStack;
//	void GetName()
//	{
//		valueName = "";
//		for (int i = 0; i < nameStack.size(); i++)
//		{
//			valueName += nameStack[i];
//			if (i != nameStack.size() - 1)
//			{
//				valueName += ".";
//			}
//		}
//	}
//
//public:
//	BinaryFileRead(){}
//
//	template<typename T>
//	void Serialize(T& data, const string& name)
//	{
//		nameStack.push_back(name);
//		SerializeTraits<T>::Serialize(data, *this);
//		nameStack.pop_back();
//	}
//
//	template<typename T>
//	void Serialize(T* data, const string& name) 
//	{
//		if (data != nullptr)
//		{
//			nameStack.push_back(name);
//			GetName();
//			nameStack.pop_back();
//		}
//	}
//};

class BinaryFileWrite
{
	std::ofstream file;
	std::vector<std::string> nameStack;
	std::vector<ValueInfo> valueInfos;
	uint32_t dataOffset = 0;
	char* dataBuffer = nullptr;
	int dataBufferSize = 1024;

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
	BinaryFileWrite(){}
	BinaryFileWrite(const char* fileName)
	{
		file.open(fileName, std::ios::binary | std::ios::out);
		dataBuffer = new char[dataBufferSize];
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

		valueInfos.push_back(ValueInfo(name.c_str(), dataOffset, sizeof(T)));
		dataOffset += sizeof(T);

		if (dataOffset + 128 >= dataBufferSize)
		{
			dataBufferSize *= 2;
			char* newDataBuffer = new char[dataBufferSize];
			memcpy(newDataBuffer, dataBuffer, dataOffset);
			delete[] dataBuffer;
			dataBuffer = newDataBuffer;
		}

		nameStack.pop_back();
	}

	void EndSerialize()
	{
		int size = 0;
		for (int i = 0; i < valueInfos.size(); i++)
		{
			size += valueInfos[i].nameStrLength;
			size += 12;
		}

		char* headBuffer = new char[size];
		int offset = 0;
		for (int i = 0; i < valueInfos.size(); i++)
		{
			offset = ValueInfo::WriteValueInfo(headBuffer, offset, valueInfos[i]);
		}

		file.write((const char*)&size, sizeof(size));
		file.write((const char*)headBuffer, size);
		file.write((const char*)dataBuffer, dataOffset);

		delete[] headBuffer;

		file.close();
	}
};
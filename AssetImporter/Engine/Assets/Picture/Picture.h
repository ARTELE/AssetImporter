#pragma once
#include <Engine/Assets/Asset.h>
#include <Engine/Serialization/Serialization.h>
#include <Engine/Systems/Allocator/SystemAllocator.h>
class Picture : public Asset
{
	int width, height, channel;
	unsigned char* data;
	SystemAllocator allocator;
public:
	Picture(int width, int height, int channel, unsigned char* data) : width(width), height(height), channel(channel), data(data) {}

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		SERIALIZE(width);
		SERIALIZE(height);
		SERIALIZE(channel);
		serializer.SetUserAllocator(&allocator);
		SERIALIZE_PTR(data, width * height * channel);
		//serializer.SetUserAllocator(nullptr);
	}
};
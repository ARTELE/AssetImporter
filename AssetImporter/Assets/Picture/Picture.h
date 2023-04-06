#pragma once
#include<Assets/Asset.h>
class Picture : public Asset
{

	int width, height, channels;
	unsigned char* data;
public:
	Picture(int width, int height, int channel, unsigned char* data) : width(width), height(height), channels(channels), data(data) {}

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{

	}
};
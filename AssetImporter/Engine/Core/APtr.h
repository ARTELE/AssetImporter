#pragma once
#include "Types.h"
#include <string>
class APtr
{
	InstanceID instanceId;
	std::string assetName;
public:
	APtr() {}

	InstanceID GetInstanceId() { return instanceId; }

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		
	}
};
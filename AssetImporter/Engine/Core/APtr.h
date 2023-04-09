#pragma once
#include "Types.h"
#include <string>
#include <Engine/Managers/Managers.h>
#include <Engine/Serialization/Serialization.h>

template<typename T>
class APtr
{
	InstanceID instanceId;
	std::string assetName;
public:
	APtr() {}
	APtr(InstanceID id) : instanceId(id) {}

	InstanceID GetInstanceId() { return instanceId; }

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		if(serializer.IsWriting())
		{
			if (instanceId > 0)
			{
				std::string assetName = Managers::assetManager.assetPool.InstanceIdToAssetPath(instanceId);
				SERIALIZE(assetName);
			}
		}
		else if (serializer.IsReading())
		{
			std::string assetName;
			SERIALIZE(assetName);
			instanceId = Managers::assetManager.assetPool.AssetPathToInstanceId(assetName);
		}
	}
};
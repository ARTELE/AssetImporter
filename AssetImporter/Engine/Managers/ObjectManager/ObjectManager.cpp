#include "ObjectManager.h"
#include <Engine/Managers/Managers.h>
#include <Engine/Modules/Log/Log.h>

Object* ObjectManager::IDToPointer(InstanceID id)
{
	auto iter = idToInstance.find(id);
	if (iter != idToInstance.end())
	{
		if (iter->second == nullptr && id > 0)
		{
			std::string assetName = Managers::assetManager.assetPool.InstanceIdToAssetPath(id);
			if (assetName == "")
			{
				ErrorMessage(std::to_string(id) + " is invalid.");
			}
			else
			{
				iter->second = AssetUtils::LoadAssetFromPath(assetName);
				iter->second->SetInstanceId(id);
			}
		}
		return iter->second;
	}
	else
	{
		ErrorMessage(std::to_string(id) + " is invalid.");
		return nullptr;
	}
}

void ObjectManager::Initialize()
{
	auto idToAssetMap = Managers::assetManager.assetPool.GetInstanceIdToAssetMap();
	for (auto& id : idToAssetMap)
	{
		idToInstance.insert(std::make_pair(id.first, nullptr));
	}
}
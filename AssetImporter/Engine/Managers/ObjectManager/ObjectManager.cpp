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
				iter->second = Managers::assetManager.LoadAssetFromPath(assetName);
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

void ObjectManager::UnloadObject(Object* object)
{
	if (object == nullptr)
	{
		return;
	}

	InstanceID id = object->GetInstanceId();
	if (id == 0)
	{
		return;
	}

	auto iter = idToInstance.find(id);
	if (iter != idToInstance.end())
	{
		return;
	}

	if (id > 0)
	{
		Managers::assetManager.UnloadAsset(object);
		iter->second = nullptr;
	}
	else
	{
		if (iter->second != nullptr)
		{
			allocator.Deallocate(iter->second);
			idToInstance.erase(id);
		}
	}
}

void ObjectManager::AddObject(Object* object)
{
	if (object == nullptr)
	{
		return;
	}

	idToInstance.insert(std::make_pair(object->GetInstanceId(), object));
}

void ObjectManager::Initialize()
{
	auto idToAssetMap = Managers::assetManager.assetPool.GetInstanceIdToAssetMap();
	for (auto& id : idToAssetMap)
	{
		idToInstance.insert(std::make_pair(id.first, nullptr));
	}
}
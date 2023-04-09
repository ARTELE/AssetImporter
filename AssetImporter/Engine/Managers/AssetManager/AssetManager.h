#pragma once
#include <Engine/Core/Types.h>
#include <Engine/Assets/AssetPool.h>
#include <Engine/Systems/Allocator/SystemAllocator.h>
#include <Engine/Assets/Picture/Picture.h>
#include <Engine/Serialization/BinaryFileSerialization.h>
#include <vector>
#include <string>

#define ASSET_TYPE_PICTURE ".bpic"

class AssetManager
{
	std::vector<std::string> assetsPaths;
	InstanceID id = 10000;
	
public:
	AssetPool assetPool;
	SystemAllocator allocator = SystemAllocator(false);
	void Initialize();
	void AddAssetPath(std::string path);
	InstanceID GenerateInstanceId() { return ++id; }
	void ScanAssetsFile(std::vector<std::string>& paths, std::vector<std::string>& assetsFilesName);

	Object* LoadAssetFromPath(std::string path)
	{
		size_t index = path.find_last_of('.');
		std::string type = path.substr(index);

		if (type == ASSET_TYPE_PICTURE)
		{
			Picture* picture = allocator.Allocate<Picture>(1, "AssetUtils");
			BINARY_FILE_SERIALIZE_READ((*picture), path.c_str());
			return picture;
		}
	}

	void UnloadAsset(Object* object)
	{
		allocator.Deallocate(object);
	}
};
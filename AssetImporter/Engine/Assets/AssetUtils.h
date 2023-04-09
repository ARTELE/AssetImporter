#pragma once
#include <Engine/Core/Types.h>
#include <Engine/Core/Object.h>
#include <Engine/Systems/Allocator/SystemAllocator.h>
#include <Engine/Serialization/BinaryFileSerialization.h>
#include "Picture/Picture.h"
#include <vector>
#include <string>

#define ASSET_TYPE_PICTURE ".bpic"

class AssetUtils
{
	static InstanceID id;
	static SystemAllocator allocator;
public:
	static InstanceID GenerateInstanceId();
	static void ScanAssetsFile(std::vector<std::string>& paths, std::vector<std::string>& assetsFilesName);
	
	static Object* LoadAssetFromPath(std::string path)
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
};

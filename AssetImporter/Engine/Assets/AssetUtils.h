#pragma once
#include <Engine/Core/Types.h>
#include <vector>
#include <string>

class AssetUtils
{
	static InstanceID id;
public:
	static InstanceID GenerateInstanceId();
	static void ScanAssetsFile(std::vector<std::string>& paths, std::vector<std::string>& assetsFilesName);
};
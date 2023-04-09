#include"AssetUtils.h"
#include "Platform/Win64/AssetUtils.h"

InstanceID AssetUtils::id = 10000;

InstanceID AssetUtils::GenerateInstanceId()
{
	return ++id;
}

void AssetUtils::ScanAssetsFile(std::vector<std::string>& paths, std::vector<std::string>& assetsFilesName)
{
	for (int i = 0; i < paths.size(); i++)
	{
		GetFilesFromPath(paths[i], assetsFilesName);
	}
}
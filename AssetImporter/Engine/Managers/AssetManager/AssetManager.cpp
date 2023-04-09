#include "AssetManager.h"

void AssetManager::AddAssetPath(std::string path)
{
	assetsPaths.push_back(path);
}

void AssetManager::Initialize()
{
	std::vector<std::string> assetFiles;
	AssetUtils::ScanAssetsFile(assetsPaths, assetFiles);

	for (int i = 0; i < assetFiles.size(); i++)
	{
		assetPool.AddAsset(std::make_pair(AssetUtils::GenerateInstanceId(), assetFiles[i]));
	}	
}

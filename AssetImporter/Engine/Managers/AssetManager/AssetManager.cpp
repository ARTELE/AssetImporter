#include "AssetManager.h"
#include "Platform/Win64/AssetUtils.h"

void AssetManager::AddAssetPath(std::string path)
{
	assetsPaths.push_back(path);
}

void AssetManager::Initialize()
{
	std::vector<std::string> assetFiles;
	ScanAssetsFile(assetsPaths, assetFiles);

	for (int i = 0; i < assetFiles.size(); i++)
	{
		assetPool.AddAsset(std::make_pair(GenerateInstanceId(), assetFiles[i]));
	}	
}

void AssetManager::ScanAssetsFile(std::vector<std::string>& paths, std::vector<std::string>& assetsFilesName)
{
	for (int i = 0; i < paths.size(); i++)
	{
		GetFilesFromPath(paths[i], assetsFilesName);
	}
}
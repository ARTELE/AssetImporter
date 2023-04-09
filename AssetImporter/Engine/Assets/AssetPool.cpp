#include "AssetPool.h"

InstanceID AssetPool::AssetPathToInstanceId(std::string assetName)
{
	auto iter = assetToInstanceId.find(assetName);
	if (iter != assetToInstanceId.end())
	{
		return iter->second;
	}
	else
	{
		return 0;
	}
}

std::string AssetPool::InstanceIdToAssetPath(InstanceID id)
{
	auto iter = instanceIdToAsset.find(id);
	if (iter != instanceIdToAsset.end())
	{
		return iter->second;
	}
	else
	{
		return "";
	}
}

void AssetPool::AddAsset(std::pair<InstanceID, std::string> asset)
{
	assetToInstanceId.insert(std::make_pair(asset.second, asset.first));
	instanceIdToAsset.insert(std::make_pair(asset.first, asset.second));
}
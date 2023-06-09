#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <Engine/Core/Types.h>
class AssetPool
{
	std::vector<std::pair<InstanceID, std::string>> assets;
	std::unordered_map<std::string, InstanceID> assetToInstanceId;
	std::unordered_map<InstanceID, std::string> instanceIdToAsset;
public:
	AssetPool() {}
	InstanceID AssetPathToInstanceId(std::string assetName);
	std::string InstanceIdToAssetPath(InstanceID id);
	void AddAsset(std::pair<InstanceID, std::string> asset);
	std::unordered_map<InstanceID, std::string> GetInstanceIdToAssetMap() { return instanceIdToAsset; }

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		
	}

};
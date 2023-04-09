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
	InstanceID AssetToInstanceId(std::string assetName);
	std::string InstanceIdToAsset(InstanceID id);
	void AddAsset(std::pair<InstanceID, std::string> asset);

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		
	}

};
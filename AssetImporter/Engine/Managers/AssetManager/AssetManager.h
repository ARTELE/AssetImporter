#pragma once
#include <Engine/Core/Types.h>
#include <Engine/Assets/AssetPool.h>
#include <Engine/Assets/AssetUtils.h>
#include <vector>
#include <string>
class AssetManager
{
	std::vector<std::string> assetsPaths;
public:
	AssetPool assetPool;
	void Initialize();
	void AddAssetPath(std::string path);
};
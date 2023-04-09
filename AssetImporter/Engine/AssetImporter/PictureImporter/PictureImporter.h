#pragma once
#include <Engine/AssetImporter/AssetImporter.h>
#include <Engine/Assets/Picture/Picture.h>
class PictureImporter : public AssetImporter
{
	int width, height, channel;
	unsigned char* data;

	virtual bool LoadFile(std::string fileName) override;
	virtual bool CreateAsset() override;
	virtual bool Destroy() override;
public:
	PictureImporter(){}
};
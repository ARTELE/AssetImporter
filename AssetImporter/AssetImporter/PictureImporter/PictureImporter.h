#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <AssetImporter/AssetImporter.h>
#include <Assets/Picture/Picture.h>
class PictureImporter : public AssetImporter
{
	int width, height, channels;
	unsigned char* data;

	virtual bool LoadFile(std::string fileName);
	virtual bool StructureData();
	virtual bool Destroy();
public:

};
#include "PictureImporter.h"
#include <Assets/Picture/Picture.h>
bool PictureImporter::LoadFile(std::string fileName)
{
	data = stbi_load(fileName.c_str(), &width, &height, &channels, 0);
	if (data == nullptr)
	{
		return false;
	}
	return true;
}

bool PictureImporter::StructureData()
{
	picture = Picture(width, height, channels, data);
	return true;
}

bool PictureImporter::Destroy()
{
	delete[] data;
	return true;
}
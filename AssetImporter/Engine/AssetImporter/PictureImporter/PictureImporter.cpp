#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "PictureImporter.h"
#include <Engine/Assets/Picture/Picture.h>
#include <Engine/Modules/Log/Log.h>
#include <Engine/Serialization/BinaryFileSerialization.h>

bool PictureImporter::LoadFile(std::string fileName)
{
	data = stbi_load(fileName.c_str(), &width, &height, &channel, 0);
	if (data == nullptr || width <= 0 || height <= 0 || channel <= 0)
	{
		ErrorMessage(fileName + " Load failed.");
		return false;
	}

	return true;
}

bool PictureImporter::CreateAsset()
{
	Picture picture(width, height, channel, data);

 	BINARY_FILE_SERIALIZE_WRITE(picture, outPutFileName.c_str());

	return true;
}

bool PictureImporter::Destroy()
{
	delete[] data;
	return true;
}
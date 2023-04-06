#include "PictureImporter.h"
#include <Assets/Picture/Picture.h>
//#include <Modules/Log/Log.h>
#include <Serialization/BinaryFileSerialization.h>
bool PictureImporter::LoadFile(std::string fileName)
{
	data = stbi_load(fileName.c_str(), &width, &height, &channels, 0);
	if (data == nullptr)
	{
		ErrorMessage(fileName + " Load failed.");
		return false;
	}

	return true;
}

bool PictureImporter::StructureData()
{
	Picture picture(width, height, channels, data);

	BINARY_FILE_SERIALIZE_WRITE(picture, inPutFileName.c_str());

	return true;
}

bool PictureImporter::Destroy()
{
	delete[] data;
	return true;
}
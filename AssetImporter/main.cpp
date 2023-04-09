#include <Engine/AssetImporter/PictureImporter/PictureImporter.h>
#include <iostream>
#include <Engine/Serialization/BinaryFileSerialization.h>
#include <Engine/Modules/Log/Log.h>

using namespace std;

int main()
{
	LogMessage("Begin");

	PictureImporter importer;
	importer.Initialize("test.jpg","picture.bpic");
	importer.Import();

	LogMessage("End");
	return 0;
}
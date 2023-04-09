#include <Engine/AssetImporter/PictureImporter/PictureImporter.h>
#include <iostream>
#include <Engine/Serialization/BinaryFileSerialization.h>
#include <Engine/Modules/Log/Log.h>
#include <Engine/Managers/Managers.h>
#include <Engine/Core/APtr.h>

using namespace std;

struct PtrTest
{
	APtr<Picture> pic;

	template<typename Serialize>
	void Serialize(Serialize& serializer)
	{
		SERIALIZE(pic);
	}
};

int main()
{
	LogMessage("Begin");

	//PictureImporter importer;
	//importer.Initialize("test.jpg","picture.bpic");
	//importer.Import();

	Managers::assetManager.AddAssetPath("Assets");
	Managers::assetManager.Initialize();
	Managers::objectManager.Initialize();


	PtrTest test;
	BINARY_FILE_SERIALIZE_READ(test, "Assets/test.ttt");
	std :: cout << test.pic->GetInstanceId();
	//test.pic = APtr<Picture>(10002);
	//BINARY_FILE_SERIALIZE_WRITE(test, "Assets/test.ttt");
	

	LogMessage("End");
	return 0;
}
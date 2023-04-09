#pragma once
#include <string>

class AssetImporter
{
protected:
	std::string inPutFileName;
	std::string outPutFileName;

	virtual bool LoadFile(std::string fileName) = 0;
	virtual bool CreateAsset() = 0;
	virtual bool Destroy()  = 0;
public:
	AssetImporter(){}
	void Initialize(std::string srcFileName, std::string dstFileName)
	{
		inPutFileName = srcFileName;
		outPutFileName = dstFileName;
	}
	bool Import()
	{
		return LoadFile(inPutFileName) && CreateAsset() && Destroy();
	}
};
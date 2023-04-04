#pragma once
#include <string>
class AssetImporter
{
	std::string inPutFileName;
	std::string outPutFileName;

	virtual bool LoadFile(std::string fileName) = 0;
	virtual bool StructureData() = 0;
	virtual bool Serialize(std::string fileName) = 0;
	virtual bool Destroy()  = 0;
public:
	AssetImporter(const std::string& in, const std::string& out) : inPutFileName(in), outPutFileName(out) {}

	bool Import()
	{
		return LoadFile(inPutFileName) || StructureData() || Serialize(outPutFileName) || Destroy();
	}


};
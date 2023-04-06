#pragma once
#include <string>
class AssetImporter
{
protected:
	std::string inPutFileName;
	std::string outPutFileName;

	virtual bool LoadFile(std::string fileName) = 0;
	virtual bool StructureData() = 0;
	virtual bool Destroy()  = 0;
public:
	AssetImporter(const std::string& in, const std::string& out) : inPutFileName(in), outPutFileName(out) {}
	void Initialize(std::string srcFileName, std::string dstFileName)
	{
		inPutFileName = srcFileName;
		outPutFileName = dstFileName;
	}
	bool Import()
	{
		return LoadFile(inPutFileName) || StructureData() || Destroy();
	}


};
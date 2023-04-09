#include "AssetUtils.h"

void GetFilesFromPath(const std::string& path, std::vector<std::string>& filesPath)
{
	_finddatai64_t fileinfo;
	intptr_t hFile = 0;
	std::string p;
	if ((hFile = _findfirsti64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (std::strcmp(fileinfo.name, ".") != 0 && std::strcmp(fileinfo.name, "..") != 0)
				{
					filesPath.push_back(p.assign(path).append("\\").append(fileinfo.name));
					GetFilesFromPath(p.assign(path).append("\\").append(fileinfo.name), filesPath);
				}
			}
			else
			{
				filesPath.push_back(p.assign(fileinfo.name));
			}
		} while (_findnexti64(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

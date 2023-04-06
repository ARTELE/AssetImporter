# CMakeList.txt: AssetImporter 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

include_directories(AssetImporter/)
include_directories(3rdlibrary/stb)
include_directories(Asset/)
include_directories(Core/)
include_directories(./)


# 将源代码添加到此项目的可执行文件。
add_executable (AssetImporter 
"main.cpp"  
"AssetImporter/AssetImporter.h"
"AssetImporter/PictureImporter/PictureImporter.h"
"AssetImporter/PictureImporter/PictureImporter.cpp" 
"Serialization/BinaryFileSerialization.h" 
"Systems/Allocator/BaseAllocator.h" 
"Systems/Allocator/SystemAllocator.h" 
"Modules/Log/Log.h" 
"Systems/Log/LogSystem.h" 
"Systems/Log/LogSystem.cpp"
"Managers/SystemsManager.h"
 "Managers/SystemsManager.cpp" 
 "Modules/Log/Log.cpp")



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AssetImporter PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

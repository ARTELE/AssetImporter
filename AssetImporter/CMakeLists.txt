# CMakeList.txt: AssetImporter 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

include_directories(3rdlibrary/stb)
include_directories(./)

#aux_source_directory(Engine ENGINE_SOURCE_LIST)
#aux_source_directory(Editor EDITOR_SOURCE_LIST)

# 将源代码添加到此项目的可执行文件。
add_executable (AssetImporter "main.cpp" 
"Engine/AssetImporter/AssetImporter.h"
"Engine/AssetImporter/PictureImporter/PictureImporter.h"
"Engine/AssetImporter/PictureImporter/PictureImporter.cpp"
"Engine/Assets/Picture/Picture.h"
"Engine/Assets/Asset.h"
"Engine/Assets/AssetPool.h"
"Engine/Assets/AssetPool.cpp"
"Engine/Core/APtr.h"
"Engine/Core/Object.h"
"Engine/Core/Types.h"
"Engine/Managers/Managers.h"
"Engine/Managers/Managers.cpp"
"Engine/Managers/AssetManager/AssetManager.h"
"Engine/Managers/AssetManager/AssetManager.cpp"
"Engine/Managers/AssetManager/Platform/Win64/AssetUtils.h"
"Engine/Managers/AssetManager/Platform/Win64/AssetUtils.cpp"
"Engine/Managers/ObjectManager/ObjectManager.h"
"Engine/Managers/ObjectManager/ObjectManager.cpp"
"Engine/Managers/SystemManager/SystemManager.h"
"Engine/Managers/SystemManager/SystemManager.cpp"
"Engine/Modules/Log/Log.h"
"Engine/Modules/Log/Log.cpp"
"Engine/Serialization/Serialization.h"
"Engine/Serialization/BinaryFileSerialization.h"
"Engine/Systems/Log/LogSystem.h"
"Engine/Systems/Log/LogSystem.cpp"
"Engine/Systems/Allocator/BaseAllocator.h"
"Engine/Systems/Allocator/SystemAllocator.h"
"Engine/Assets/Picture/Picture.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AssetImporter PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

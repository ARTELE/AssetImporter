#pragma once
#include "SystemManager/SystemManager.h"
#include "AssetManager/AssetManager.h"
#include "ObjectManager/ObjectManager.h"

class Managers
{
public:
	static SystemsManager systemManager;
	static AssetManager assetManager;
	static ObjectManager objectManager;
};
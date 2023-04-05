#pragma once
#include <Systems/Log/LogSystem.h>
class SystemsManager
{
public:
	static LogSystem logSystem;
};

LogSystem SystemsManager::logSystem;
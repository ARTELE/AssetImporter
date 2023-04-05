#pragma once
#include <Managers/SystemsManager.h>
#include <string>

void LogMessage(std::string message)
{
	SystemsManager::logSystem.Log(message);
}

void DebugLogMessage(std::string message)
{
#if _DEBUG
	SystemsManager::logSystem.Log(message);
#endif
}

void WarningMessage(std::string message)
{
	SystemsManager::logSystem.Warning(message);
}

void DebugWarningMessage(std::string message)
{
#if _DEBUG
	SystemsManager::logSystem.Warning(message);
#endif
}

void ErrorMessage(std::string message)
{
	SystemsManager::logSystem.Error(message);
}

void DebugErrorMessage(std::string message)
{
#if _DEBUG
	SystemsManager::logSystem.Error(message);
#endif
}
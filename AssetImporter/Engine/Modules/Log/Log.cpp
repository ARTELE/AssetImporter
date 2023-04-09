#pragma once
#include "Log.h"
#include <Engine/Managers/Managers.h>
#include <string>

void LogMessage(std::string message)
{
	Managers::systemManager.logSystem.Log(message);
}

void DebugLogMessage(std::string message)
{
#if _DEBUG
	Managers::systemManager.logSystem.Log(message);
#endif
}

void WarningMessage(std::string message)
{
	Managers::systemManager.logSystem.Warning(message);
}

void DebugWarningMessage(std::string message)
{
#if _DEBUG
	Managers::systemManager.logSystem.Warning(message);
#endif
}

void ErrorMessage(std::string message)
{
	Managers::systemManager.logSystem.Error(message);
}

void DebugErrorMessage(std::string message)
{
#if _DEBUG
	Managers::systemManager.logSystem.Error(message);
#endif
}
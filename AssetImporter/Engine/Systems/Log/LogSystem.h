#pragma once
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <mutex>
#include <fstream>

class LogSystem
{
	enum LogLevel
	{
		LOG = 0,
		WARNIMG = 1,
		ERROR = 2,
	};
	std::mutex mutex;
	std::ofstream logFile;

	bool consoleMessage = true;
	bool fileMessage = true;
	bool asyncOutPut = false;
	std::vector<std::tuple<std::string, std::string, LogLevel>> messageQueue;

	std::string GetTimeStamp();
	void OutPutMessage(std::tuple<std::string, std::string, LogLevel> message);

public:
	LogSystem() { logFile.open("EngineLog.log"); }
	
	void Log(std::string message);
	void Warning(std::string message);
	void Error(std::string message);
	void WriteMessage();
};
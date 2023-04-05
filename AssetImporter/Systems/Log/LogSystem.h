#pragma once
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <mutex>

class LogSystem
{
	enum LogLevel
	{
		LOG = 0,
		WARNIMG = 1,
		ERROR = 2,
	};
	std::mutex mutex;

	bool consoleMessage = true;
	bool fileMessage = true;
	bool asyncOutPut = false;
	std::vector<std::tuple<std::string, std::string, LogLevel>> messageQueue;

	std::string GetTimeStamp();
	void OutPutMessage(std::tuple<std::string, std::string, LogLevel> message);

public:
	LogSystem() {}
	
	void Log(std::string message);
	void Warning(std::string message);
	void Error(std::string message);
	void WriteMessage();
};
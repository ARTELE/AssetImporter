#include "LogSystem.h"

std::string LogSystem::GetTimeStamp()
{
	time_t nowTime;
	nowTime = time(NULL);
	tm* localTime;
	localTime = localtime(&nowTime);
	std::string timeStamp;
	timeStamp += std::to_string(localTime->tm_year + 1900);
	timeStamp += "-";
	timeStamp += std::to_string(localTime->tm_mon + 1);
	timeStamp += "-";
	timeStamp += std::to_string(localTime->tm_mday);
	timeStamp += " ";
	timeStamp += std::to_string(localTime->tm_hour);
	timeStamp += ":";
	timeStamp += std::to_string(localTime->tm_min);
	timeStamp += ":";
	timeStamp += std::to_string(localTime->tm_sec);

	return timeStamp;
}

void LogSystem::OutPutMessage(std::tuple<std::string, std::string, LogLevel> message)
{
	if (consoleMessage)
	{
		std::cout << "[" + std::get<0>(message) + "]";
		switch (std::get<2>(message))
		{
		case LogLevel::LOG:
			std::cout << "[LOG]";
			break;

		case LogLevel::WARNIMG:
			std::cout << "[WARNING]";
			break;

		case LogLevel::ERROR:
			std::cout << "[ERROR]";
			break;

		default: break;
		}
		std::cout << std::get<1>(message) << std::endl;
	}
}

void LogSystem::Log(std::string message)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (asyncOutPut)
	{
		std::string timeStamp = GetTimeStamp();
		messageQueue.push_back(std::make_tuple(timeStamp, message, LogLevel::LOG));
	}
	else
	{
		std::string timeStamp = GetTimeStamp();
		OutPutMessage(std::make_tuple(timeStamp, message, LogLevel::LOG));
	}
}

void LogSystem::Warning(std::string message)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (asyncOutPut)
	{
		std::string timeStamp = GetTimeStamp();
		messageQueue.push_back(std::make_tuple(timeStamp, message, LogLevel::WARNIMG));
	}
	else
	{
		std::string timeStamp = GetTimeStamp();
		OutPutMessage(std::make_tuple(timeStamp, message, LogLevel::WARNIMG));
	}
}

void LogSystem::Error(std::string message)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (asyncOutPut)
	{
		std::string timeStamp = GetTimeStamp();
		messageQueue.push_back(std::make_tuple(timeStamp, message, LogLevel::ERROR));
	}
	else
	{
		std::string timeStamp = GetTimeStamp();
		OutPutMessage(std::make_tuple(timeStamp, message, LogLevel::ERROR));
	}
}

void LogSystem::WriteMessage()
{
	for (int i = 0; i < messageQueue.size(); i++)
	{
		OutPutMessage(messageQueue[i]);
	}
	messageQueue.clear();
}
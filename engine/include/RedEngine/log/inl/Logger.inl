#pragma once
#include <fmt/format.h>

#include <RedEngine/Engine.hpp>
#include <iostream>

namespace red
{

template <typename... Args>
void LogTrace(std::string format, Args... args)
{
    GetRedInstance().GetLogger().LogInternal(LogLevel::TRACE, format, std::forward<Args>(args)...);
}

template <typename... Args>
void LogInfo(std::string format, Args... args)
{
    GetRedInstance().GetLogger().LogInternal(LogLevel::INFO, format, std::forward<Args>(args)...);
}

template <typename... Args>
void LogWarning(std::string format, Args... args)
{
    GetRedInstance().GetLogger().LogInternal(LogLevel::WARNING, format, std::forward<Args>(args)...);
}

template <typename... Args>
void LogError(std::string format, Args... args)
{
    GetRedInstance().GetLogger().LogInternal(LogLevel::ERROR, format, std::forward<Args>(args)...);
}

template <typename... Args>
void LogFatal(std::string format, Args... args)
{
    GetRedInstance().GetLogger().LogInternal(LogLevel::FATAL, format, std::forward<Args>(args)...);
}

template <typename... Args>
void Logger::LogInternal(LogLevel level, std::string format, Args... args)
{
    if (level >= m_logLevel)
    {
        std::string logString = fmt::format(FMT_STRING("{}"), format, std::forward<Args>(args)...);
        std::string levelAsString = g_logLevelAsString.at(level);
        std::string levelFormat = fmt::format(FMT_STRING("[{:<7}] "), levelAsString);

        Out(levelFormat + logString + '\n');
    }
}


}  // namespace red

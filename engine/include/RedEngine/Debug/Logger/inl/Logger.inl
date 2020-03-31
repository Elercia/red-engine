#pragma once

#include <fmt/format.h>

#include <iostream>
#include <map>

#include "../../../Core/Engine.hpp"

namespace red
{
template <typename... Args>
void Logger::LogInternal(LogLevel::Enum level, int line, const char* file,
                         const std::string& format, Args... args)
{
    const std::map<LogLevel::Enum, std::string> logLevelAsString{
        {LogLevel::LEVEL_TRACE, "TRACE"},     {LogLevel::LEVEL_INFO, "INFO"},
        {LogLevel::LEVEL_WARNING, "WARNING"}, {LogLevel::LEVEL_ERROR, "ERROR"},
        {LogLevel::LEVEL_FATAL, "FATAL"},
    };

    if (level >= m_logLevel)
    {
        std::string levelAsString = logLevelAsString.at(level);
        std::string levelFormat =
            fmt::format(FMT_STRING("[FILE:{}][LINE:{}] [{:<7}] "), file, line, levelAsString);

        std::string logString = fmt::format(format, std::forward<Args>(args)...);

        Out(levelFormat + logString);
    }
}

}  // namespace red

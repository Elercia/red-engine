#pragma once

#include <filesystem>
#include <fmt/format.h>
#include <iostream>
#include <map>

namespace red
{
template <typename... Args>
void Logger::LogInternal(LogLevel::Enum level, int line, const char* file, const std::string& format, Args... args)
{
    const std::map<LogLevel::Enum, std::string> logLevelAsString{
        {LogLevel::LEVEL_TRACE, "TRACE"},     {LogLevel::LEVEL_DEBUG, "DEBUG"}, {LogLevel::LEVEL_INFO, "INFO"},
        {LogLevel::LEVEL_WARNING, "WARNING"}, {LogLevel::LEVEL_ERROR, "ERROR"}, {LogLevel::LEVEL_FATAL, "FATAL"},
    };

    if (level >= m_logLevel)
    {
        std::string levelAsString = logLevelAsString.at(level);
        std::string fileFormat = std::string(file);
        fileFormat = fileFormat.substr(fileFormat.find_last_of(std::filesystem::path::preferred_separator) + 1);
        std::string levelFormat =
            fmt::format(FMT_STRING("[FILE:{}][LINE:{}] [{:<7}] "), fileFormat, line, levelAsString);

        std::string logString = fmt::format(format, std::forward<Args>(args)...);

        Out(levelFormat + logString);
    }
}

}  // namespace red

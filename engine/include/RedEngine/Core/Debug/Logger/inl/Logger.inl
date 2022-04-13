#pragma once

#include "RedEngine/Core/Container/Map.hpp"

#include <filesystem>
#include <fmt/format.h>
#include <iostream>

namespace red
{
template <typename... Args>
void Logger::LogInternal(LogLevel level, int line, const char* file, const std::string& format, Args... args)
{
    if (level >= m_logLevel)
    {
        std::string levelAsString = logLevelAsString.at(level);
        std::string fileFormat = std::string(file);
        fileFormat = fileFormat.substr(fileFormat.find_last_of(std::filesystem::path::preferred_separator) + 1);
        std::string levelFormat =
            fmt::format(FMT_STRING("[{}({})] [{}] "), fileFormat, line, levelAsString);

        std::string logString = fmt::format(format, std::forward<Args>(args)...);

        LogOoutputInfo info;
        info.str = levelFormat + logString;
        info.level = level;
        Out(info);
    }
}

}  // namespace red

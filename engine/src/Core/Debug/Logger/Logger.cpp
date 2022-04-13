#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include <fmt/core.h>

namespace red
{
const Map<LogLevel, std::string> Logger::logLevelAsString{
    {LogLevel::LEVEL_CUSTOM, "CUSTOM"}, {LogLevel::LEVEL_TRACE, "TRACE"},     {LogLevel::LEVEL_DEBUG, "DEBUG"}, {LogLevel::LEVEL_INFO, "INFO"},
    {LogLevel::LEVEL_WARNING, "WARNING"}, {LogLevel::LEVEL_ERROR, "ERROR"}, {LogLevel::LEVEL_FATAL, "FATAL"},
};

void SetLogLevel(LogLevel level)
{
    GetRedLogger()->SetLogLevel(level);
}

Logger::Logger() : m_logLevel(LogLevel::LEVEL_INFO)
{
}

void Logger::SetLogLevel(LogLevel level)
{
    m_logLevel = level;
}

void Logger::Out(const LogOoutputInfo& data)
{
    m_delegates(data);
}

Logger::OutputDelegate::FuncIndex Logger::AddOutput(OutputDelegate::FuncType output)
{
    return m_delegates.Add(std::move(output));
}

void Logger::LogToStandardOutputFun(const LogOoutputInfo& out)
{
    fmt::print(out.str);
    std::putc('\n', stdout);
}

template <>
std::string Serialize(const LogLevel& value)
{
    for (const auto& pair : Logger::logLevelAsString)
    {
        if (pair.first == value)
            return pair.second;
    }

    return "UNKNOWN";
}

template <>
bool Deserialize(LogLevel& value, const std::string& str)
{
    for (auto& pair : Logger::logLevelAsString)
    {
        if (pair.second == str)
        {
            value = pair.first;
            return true;
        }
    }

    return false;
}

}  // namespace red

red::Logger* GetRedLogger()
{
    static red::Logger logger;

    return &logger;
}

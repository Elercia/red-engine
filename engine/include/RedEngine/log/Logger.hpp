#pragma once

#include <string>
#include <map>

namespace red
{
typedef enum LogLevel
{
    TRACE,
    INFO,
    WARNING,
    ERROR,
    FATAL
} LogLevel;

const std::map<LogLevel, std::string> g_logLevelAsString = {
    {LogLevel::TRACE,     "TRACE"},
    {LogLevel::INFO,      "INFO"},
    {LogLevel::WARNING,   "WARNING"},
    {LogLevel::ERROR,     "ERROR"},
    {LogLevel::FATAL,     "FATAL"},
};

void SetLogLevel(LogLevel level);

template <typename... Args>
void LogTrace(std::string format, Args... args);

template <typename... Args>
void LogInfo(std::string format, Args... args);

template <typename... Args>
void LogWarning(std::string format, Args... args);

template <typename... Args>
void LogError(std::string format, Args... args);

template <typename... Args>
void LogFatal(std::string format, Args... args);

class Logger
{
public:
    Logger();
    ~Logger() = default;

    void SetLogLevel(LogLevel level);

    template <typename... Args>
    void LogInternal(LogLevel level, std::string format, Args... args);

protected:
    virtual void Out(const std::string& data);
private:
    LogLevel m_logLevel;
};

}  // namespace red

#include "inl/Logger.inl"
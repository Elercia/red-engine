#pragma once

#include <iostream>
#include <string>

namespace red
{

enum class LogLevel
{
    LEVEL_TRACE,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_FATAL
};

void SetLogLevel(LogLevel level);

class Logger
{
public:
    Logger();
    virtual ~Logger() = default;

    void SetLogLevel(LogLevel level);

    template <typename... Args>
    void LogInternal(LogLevel level, int line, const char* file, const std::string& format, Args... args);

protected:
    virtual void Out(const std::string& data)
    {
        std::cout << data << std::endl;
    }

private:
    LogLevel m_logLevel;
};

}  // namespace red

red::Logger* GetRedLogger();

#define RED_LOG(LEVEL, MSG, ...) GetRedLogger()->LogInternal(LEVEL, __LINE__, __FILE__, MSG, ##__VA_ARGS__)

#define RED_LOG_TRACE(MSG, ...) RED_LOG(LogLevel::LEVEL_TRACE, MSG, ##__VA_ARGS__)
#define RED_LOG_DEBUG(MSG, ...) RED_LOG(LogLevel::LEVEL_DEBUG, MSG, ##__VA_ARGS__)
#define RED_LOG_INFO(MSG, ...) RED_LOG(LogLevel::LEVEL_INFO, MSG, ##__VA_ARGS__)
#define RED_LOG_WARNING(MSG, ...) RED_LOG(LogLevel::LEVEL_WARNING, MSG, ##__VA_ARGS__)
#define RED_LOG_ERROR(MSG, ...) RED_LOG(LogLevel::LEVEL_ERROR, MSG, ##__VA_ARGS__)
#define RED_LOG_FATAL(MSG, ...) RED_LOG(LogLevel::LEVEL_FATAL, MSG, ##__VA_ARGS__)

#include "inl/Logger.inl"
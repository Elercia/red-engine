#pragma once

#include "RedEngine/Core/Event/Delegate.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"

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

template <>
std::string Serialize(const LogLevel &value);
template <>
bool Deserialize(LogLevel &value, const std::string &str);

void SetLogLevel(LogLevel level);

class Logger
{
public:

    static const Map<LogLevel, std::string> logLevelAsString;

    using OutputDelegate = Delegate<const std::string& /*Log message*/>;

    Logger();
    ~Logger() = default;

    void SetLogLevel(LogLevel level);

    template <typename... Args>
    void LogInternal(LogLevel level, int line, const char* file, const std::string& format, Args... args);

    void Out(const std::string& str);

    OutputDelegate::FuncIndex AddOutput(OutputDelegate::FuncType output);

    static void LogToStandardOutputFun(const std::string& out);

private:
    LogLevel m_logLevel;
    OutputDelegate m_delegates;
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
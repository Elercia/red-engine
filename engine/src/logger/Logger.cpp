#include <RedEngine/log/Logger.hpp>

namespace red
{
Logger::Logger() : m_logLevel(LogLevel::INFO) {}

void Logger::SetLogLevel(LogLevel level) { m_logLevel = level; }

void SetLogLevel(LogLevel level) { GetRedInstance().GetLogger().SetLogLevel(level); }

void Logger::Out(const std::string& data) { std::cout << data; }
}  // namespace red
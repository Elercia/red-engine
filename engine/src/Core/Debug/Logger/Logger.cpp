#include "RedEngine/Core/CoreModule.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
void SetLogLevel(LogLevel::Enum level) { GetRedLogger()->SetLogLevel(level); }

Logger::Logger() : m_logLevel(LogLevel::LEVEL_INFO) {}

void Logger::SetLogLevel(LogLevel::Enum level) { m_logLevel = level; }

void Logger::Out(const std::string& data) { std::cout << data << std::endl; }

}  // namespace red

red::Logger* GetRedLogger()
{
    static red::Logger logger;

    return &logger;
}

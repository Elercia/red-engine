#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include "RedEngine/Core/CoreModule.hpp"

namespace red
{
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

void Logger::Out(const std::string& str)
{
    m_delegates(str);
}

Logger::OutputDelegate::FuncIndex Logger::AddOutput(OutputDelegate::FuncType output)
{
    return m_delegates.Add(std::move(output));
}

void Logger::LogToStandardOutputFun(const std::string& out)
{
    std::cout << out << "\n";
}

}  // namespace red

red::Logger* GetRedLogger()
{
    static red::Logger logger;

    return &logger;
}

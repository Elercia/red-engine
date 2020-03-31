#pragma once

#include <RedEngine/Debug/Logger/Logger.hpp>

class LoggerTest : public red::Logger
{
protected:
    virtual void Out(const std::string& data) override { lastLog = std::string(data.c_str()); }

public:
    std::string lastLog;
};

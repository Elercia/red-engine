#pragma once

#include <RedEngine/log/Logger.hpp>

class LoggerTest : public red::Logger
{
protected:
    virtual void Out(const std::string& data) override { lastLog = data; }

public:
    std::string lastLog;
};

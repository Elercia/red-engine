#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

class LoggerTest : public red::Logger
{
public:
    LoggerTest() = default;
    virtual ~LoggerTest() = default;

protected:

    void Out(const std::string& data) override { lastLog = data; }

public:
    std::string lastLog;
};

#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

class Logger4Test : public red::Logger
{
public:
    Logger4Test() = default;
    virtual ~Logger4Test() = default;

protected:

    virtual void Out(const std::string& data) override { lastLog = data; }

public:
    std::string lastLog;
};

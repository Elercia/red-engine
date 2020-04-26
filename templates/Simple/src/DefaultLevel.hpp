#pragma once

#include <RedEngine/Level/Level.hpp>

class DefaultLevel : public red::Level
{
public:
    DefaultLevel() : red::Level("Test"){};
    ~DefaultLevel() override = default;
    ;
};

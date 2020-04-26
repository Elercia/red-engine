#pragma once

#include <RedEngine/Level/Level.hpp>

class DefaultLevel : public red::Level
{
public:
    DefaultLevel() : red::Level("DefaultLevel"){};
    ~DefaultLevel() override = default;

    void Init() override;
    void Finalize() override;
};

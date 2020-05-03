#pragma once

#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Level/Level.hpp>

class DefaultLevel : public red::Level
{
public:
    DefaultLevel() : red::Level("DefaultLevel"){};
    ~DefaultLevel() override = default;

    void Init(red::World& world) override;
    void Finalize() override;
};

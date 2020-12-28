#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/Level.hpp"

class PongLevel : public red::Level
{
public:
    explicit PongLevel(red::World* world) : red::Level("PongLevel", world){};
    ~PongLevel() override = default;

    void Init() override;
    void Finalize() override;
};

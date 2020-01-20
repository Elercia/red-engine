#pragma once

#include <RedEngine/ecs/System.hpp>

class CustomSystem : public red::System
{
public:
    void Update(float deltaTime) override;
};

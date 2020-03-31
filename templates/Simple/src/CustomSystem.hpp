#pragma once

#include <RedEngine/Core/Entity/System.hpp>

class CustomSystem : public red::System
{
public:
    void Update(float deltaTime) override;
};

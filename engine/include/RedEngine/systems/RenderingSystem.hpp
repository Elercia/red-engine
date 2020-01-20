#pragma once

#include <RedEngine/ecs/System.hpp>

namespace red
{

class RenderingSystem : public System
{
public:
    RenderingSystem(ComponentManager* componentManager);

    void Update(float deltaTime) override;
};

} // namespace red

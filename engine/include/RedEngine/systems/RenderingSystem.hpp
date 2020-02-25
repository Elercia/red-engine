#pragma once

#include <RedEngine/ecs/System.hpp>

namespace red
{
class RenderingSystem : public System
{
public:
    RenderingSystem(World* world);

    void Update(float deltaTime) override;
};

}  // namespace red

#pragma once

#include "../Core/Entity/System.hpp"

namespace red
{
class RenderingEngine;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);

    void Update(float deltaTime) override;

private:
    RenderingEngine* m_renderingEngine;
};

}  // namespace red

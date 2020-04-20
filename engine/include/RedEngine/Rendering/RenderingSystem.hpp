#pragma once

#include "../Core/Entity/System.hpp"

namespace red
{
class RenderingEngine;
class ResourceEngine;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);

    void Update(float deltaTime) override;

    void Finalise() override;

private:
    RenderingEngine* m_renderingEngine;
    ResourceEngine* m_resourceEngine;
};

}  // namespace red

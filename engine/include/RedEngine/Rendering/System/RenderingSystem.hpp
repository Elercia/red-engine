#pragma once

#include <RedEngine/Rendering/Component/CameraComponent.hpp>

#include "../../Core/Entity/System.hpp"

namespace red
{
class RenderingEngine;
class ResourceEngine;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);

    void PreUpdate() override;
    void Update() override;
    void LateUpdate() override;

private:
    RenderingEngine* m_renderingEngine;
    ResourceEngine* m_resourceEngine;
};

}  // namespace red

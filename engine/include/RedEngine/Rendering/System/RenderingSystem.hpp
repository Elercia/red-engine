#pragma once

#include <RedEngine/Rendering/Component/CameraComponent.hpp>

#include "../../Core/Entity/System.hpp"

namespace red
{
class RenderingEngine;
class ResourceEngine;
class CameraComponent;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);

    void PreUpdate() override;
    void Update() override;
    void LateUpdate() override;

private:
    void DrawDebug(CameraComponent* camera);

private:
    RenderingEngine* m_renderingEngine;
    ResourceEngine* m_resourceEngine;
};

}  // namespace red

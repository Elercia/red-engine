#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Renderer.hpp"

namespace red
{
class CameraComponent;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);

    virtual void Init() override;

    void PreUpdate() override;
    void Update() override;
    void PostUpdate() override;

    Renderer* GetRenderer();

private:
    void DrawDebug(CameraComponent* camera);

private:
    Renderer* m_renderer;
};

}  // namespace red

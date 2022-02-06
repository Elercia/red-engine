#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class CameraComponent;
class Renderer;

class RenderingSystem : public System
{
public:
    explicit RenderingSystem(World* world);
    virtual ~RenderingSystem() = default;

    virtual void Init() override;
    virtual void Finalise() override;

    void Update() override;

    virtual void BeginRender() override;
    virtual void Render() override;
    virtual void EndRender() override;

    Renderer* GetRenderer();

private:
    void DrawDebug(CameraComponent* camera);
    void UpdateWindowAsNeeded();

private:
    Renderer* m_renderer;
};

}  // namespace red

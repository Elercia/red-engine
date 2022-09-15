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

    virtual void Update() override;

    virtual void BeginRender() override;
    virtual void EndRender() override;

    Renderer* GetRenderer();

private:
    void RenderDebug();
    void UpdateWindowAsNeeded();
    Array<CameraComponent*, DoubleLinearArrayAllocator> GetSortedCameras();

private:
    Renderer* m_renderer;
};

}  // namespace red

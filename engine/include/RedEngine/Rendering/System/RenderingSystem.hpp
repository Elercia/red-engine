#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class CameraComponent;
class Renderer;

class RenderingSystem : public System<QueryRO<Renderable>>
{
public:
    explicit RenderingSystem(World* world);
    virtual ~RenderingSystem() = default;

    virtual void Init() override;
    virtual void Finalize() override;

    virtual void Update() override;

    Renderer* GetRenderer();

private:
    void DrawDebug();
    void UpdateWindowAsNeeded();
    Array<CameraComponent*, DoubleLinearArrayAllocator> GetSortedCameras();

private:
    Renderer* m_renderer;
};

}  // namespace red

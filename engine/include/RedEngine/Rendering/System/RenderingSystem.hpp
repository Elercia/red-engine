#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class CameraComponent;
class Renderer;

class RenderingSystem : public System<QueryGroup<QueryRO<Transform>, QueryRO<Renderable>>,
                                      QueryGroup<QueryRW<DebugComponent>>, QueryGroup<QueryRW<CameraComponent>>>
{
public:
    explicit RenderingSystem(World* world);
    virtual ~RenderingSystem() = default;

    virtual void Init() override;
    virtual void Finalize() override;

    virtual void Update() override;

    void BeginRendering();

    Renderer* GetRenderer();

private:
    void DrawDebug();
    Array<CameraComponent*, DoubleLinearArrayAllocator> GetSortedCameras();

private:
    Renderer* m_renderer;
};

}  // namespace red

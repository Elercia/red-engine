#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class CameraComponent;
class RendererComponent;
class Renderable;
class DebugComponent;

class BeginNextFrameRenderingSystem : public System<SinglQuery<QueryRW<RendererComponent>>>
{
public:
    BeginNextFrameRenderingSystem(World* world);

    virtual void Init() override;

    virtual void Update() override;
};

class UpdateRenderableSystem
    : public System<QueryGroup<QueryRO<Transform>, QueryRO<Renderable>>, SinglQuery<QueryRW<RendererComponent>>>
{
public:
    UpdateRenderableSystem(World* world);

    virtual void Update() override;
};

class FlushRenderSystem : public System<QueryGroup<QueryRO<Transform>, QueryRW<CameraComponent>>,
                                        SinglQuery<QueryRW<RendererComponent>>, SinglQuery<QueryRW<DebugComponent>>>
{
public:
    FlushRenderSystem(World* world);

    virtual void Update() override;
};

//, QueryGroup<QueryRW<DebugComponent>>, QueryGroup<QueryRW<CameraComponent>>

}  // namespace red

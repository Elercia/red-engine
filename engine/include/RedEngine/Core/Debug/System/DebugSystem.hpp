#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include <RedEngine/Rendering/Component/RendererComponent.hpp>

namespace red
{
class DebugComponent;
class EventsComponent;

class DebugSystem : public System<SinglQuery<QueryRW<DebugComponent>>, 
                                    SinglQuery<QueryRO<EventsComponent>>,
                                  QueryGroup<QueryRO<Transform>>, SinglQuery<QueryRW<RendererComponent>>>
{
public:
    explicit DebugSystem(World* world);
    ~DebugSystem() override = default;

    virtual void Init() override;

    void Update() override;

private:
    static void RenderConsole(DebugComponent* debug);
    static void RenderEntityTree(DebugComponent* debug);
    static void RenderDebugPhysicsControls(DebugComponent* debug);
};
}  // namespace red

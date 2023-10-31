#include "RedEngine/Rendering/System/RenderingSystem.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/RendererComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Renderer.hpp"

#include <SDL2/SDL.h>
#include <algorithm>

namespace red
{

BeginNextFrameRenderingSystem::BeginNextFrameRenderingSystem(World* world)
    : System<SinglQuery<QueryRW<RendererComponent>>>(world)
{
}

void BeginNextFrameRenderingSystem::Init()
{
    System::Init();

    auto* window = m_world->CreateWorldEntity("Window")->AddComponent<WindowComponent>();
    auto* rendererComp = m_world->CreateWorldEntity("Renderer")->AddComponent<RendererComponent>();

    rendererComp->GetRenderer().InitRenderer(window);
}

void BeginNextFrameRenderingSystem::Update()
{
    PROFILER_EVENT_CATEGORY("BeginNextFrameRenderingSystem::Update", ProfilerCategory::Rendering);

    QuerySingletonComponent<0>()->GetRenderer().BeginRenderFrame();
}

UpdateRenderableSystem::UpdateRenderableSystem(World* world)
    : System<QueryGroup<QueryRO<Transform>, QueryRO<Renderable>>, SinglQuery<QueryRW<RendererComponent>>>(world)
{
}

void UpdateRenderableSystem::Update()
{
    PROFILER_EVENT_CATEGORY("UpdateRenderableSystem::Update", ProfilerCategory::Rendering);

    auto renderableEntities = QueryComponents<0>();
    auto renderer = QuerySingletonComponent<1>();

    for (auto& comps : renderableEntities)
    {
        auto transform = std::get<0>(comps);
        auto renderable = std::get<1>(comps);
        if (!renderable->IsValid())
            continue;

        renderer->GetRenderer().Draw(renderable.Get(), transform.Get());
    }
}

FlushRenderSystem::FlushRenderSystem(World* world)
    : System<QueryGroup<QueryRO<Transform>, QueryRW<CameraComponent>>, SinglQuery<QueryRW<RendererComponent>>,
             SinglQuery<QueryRW<DebugComponent>>>(world)
{
}

void FlushRenderSystem::Update()
{
    PROFILER_EVENT_CATEGORY("FlushRenderSystem::Update", ProfilerCategory::Rendering)

    auto& renderer = QuerySingletonComponent<1>()->GetRenderer();
    auto debugComponent = QuerySingletonComponent<2>();

    auto cameraEntities = QueryComponents<0>();
    Array<CameraComponent*, DoubleLinearArrayAllocator> cameras;
    cameras.resize(cameraEntities.size());
    std::transform(cameraEntities.begin(), cameraEntities.end(), cameras.begin(),
                   [](auto& t)
                   {
                       auto cameraQuery = std::get<1>(t);
                       cameraQuery->UpdateState();
                       return cameraQuery.Get();
                   });

    std::sort(cameras.begin(), cameras.end(),
              [](const CameraComponent* l, const CameraComponent* r) { return l->Depth() < r->Depth(); });

    for (auto& cameraComponent : cameras)
    {
        renderer.BeginCameraRendering(cameraComponent); // TODO should be externalized ?

        renderer.RenderSprites(cameraComponent);

#ifdef RED_DEVBUILD
        renderer.RenderDebug(cameraComponent, debugComponent.Get());
#endif

        renderer.EndCameraRendering(cameraComponent);
    }

#ifdef RED_DEVBUILD
    renderer.RenderFullScreenDebugUI();

    debugComponent->ClearDebug();
#endif

    renderer.EndRenderFrame();
}

}  // namespace red

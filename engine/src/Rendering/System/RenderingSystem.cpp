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
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Renderer.hpp"

#include <SDL2/SDL.h>
#include <algorithm>

namespace red
{
RenderingSystem::RenderingSystem(World* world) : System(world), m_renderer(nullptr)
{
}

void RenderingSystem::Init()
{
    if (m_renderer != nullptr)
        return;

    System::Init();

    auto* window = m_world->CreateWorldEntity("Window")->AddComponent<WindowComponent>();

    m_renderer = new Renderer;
    m_renderer->InitRenderer(window);
}

void RenderingSystem::Finalize()
{
    m_renderer->Finalise();
    RED_SAFE_DELETE(m_renderer);

    System::Finalize();
}

void RenderingSystem::Update()
{
    PROFILER_EVENT_CATEGORY("Update render data", ProfilerCategory::Rendering);

    auto renderableEntities = QueryComponents<0>();

    for (auto& comps : renderableEntities)
    {
        auto transform = std::get<0>(comps);
        auto renderable = std::get<1>(comps);
        if (!renderable->IsValid())
            continue;

        m_renderer->Draw(renderable.Get(), transform.Get());
    }

    DrawDebug();

    {
        PROFILER_EVENT_CATEGORY("Flush rendering", ProfilerCategory::Rendering);

        // Draw frame for each camera
        auto cameras = GetSortedCameras();

        for (auto& cameraComponent : cameras)
        {
            m_renderer->BeginCameraRendering(cameraComponent);

            m_renderer->RenderOpaqueQueue(cameraComponent);
            m_renderer->RenderTransparencyQueue(cameraComponent);

#ifdef RED_DEVBUILD
            auto* debugComp = m_world->GetWorldComponent<DebugComponent>();
            m_renderer->RenderDebug(cameraComponent, debugComp);
#endif

            m_renderer->EndCameraRendering(cameraComponent);
        }

#ifdef RED_DEVBUILD
        m_renderer->RenderDebugUI();

        auto debug = std::get<0>(QueryComponents<1>()[0]);  // TODO Do something about fetching only one component
        debug->ClearDebug();
#endif

        m_renderer->EndRenderFrame();
    }
}
void RenderingSystem::BeginRendering()
{
    PROFILER_EVENT_CATEGORY("Begin rendering", ProfilerCategory::Rendering);

    m_renderer->BeginRenderFrame();
}

Renderer* RenderingSystem::GetRenderer()
{
    return m_renderer;
}

void RenderingSystem::DrawDebug()
{
    PROFILER_EVENT_CATEGORY("DrawDebug", ProfilerCategory::Rendering);

    m_world->GetPhysicsWorld()->DrawDebug();  // FIXME, should be inside the debug system
}

Array<CameraComponent*, DoubleLinearArrayAllocator> RenderingSystem::GetSortedCameras()
{
    PROFILER_EVENT_CATEGORY("RenderingSystem::GetSortedCameras", ProfilerCategory::Rendering)

    auto cameraEntities = QueryComponents<2>();
    Array<CameraComponent*, DoubleLinearArrayAllocator> cameras;
    cameras.resize(cameraEntities.size());
    std::transform(cameraEntities.begin(), cameraEntities.end(), cameras.begin(),
                   [](auto& t)
                   {
                       auto cameraQuery = std::get<0>(t);
                       cameraQuery->UpdateState();
                       return cameraQuery.Get();
                   });

    std::sort(cameras.begin(), cameras.end(),
              [](const CameraComponent* l, const CameraComponent* r) { return l->Depth() < r->Depth(); });

    return cameras;
}

}  // namespace red

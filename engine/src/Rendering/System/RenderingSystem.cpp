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
    m_priority = 100;
}

void RenderingSystem::Init()
{
    System::Init();

    auto* window = m_world->CreateWorldEntity("Window")->AddComponent<WindowComponent>();

    m_renderer = new Renderer;
    m_renderer->InitRenderer(window);
}

void RenderingSystem::Finalise()
{
    m_renderer->Finalise();
    RED_SAFE_DELETE(m_renderer);

    System::Finalise();
}

void RenderingSystem::Update()
{
    PROFILER_EVENT_CATEGORY("Update render data", ProfilerCategory::Rendering);

    auto spriteEntities = GetComponents<Sprite>();

    for (auto& comps : spriteEntities)
    {
        auto* spriteEntity = std::get<0>(comps);
        auto* sprite = std::get<1>(comps);
        if (!sprite->IsValid())
            continue;

        auto* transform = spriteEntity->GetComponent<Transform>();

        sprite->NextFrame();

        // Push this entity to the list of entity to render
        m_renderer->Draw(sprite, transform);
    }

    DrawDebug();
}

void RenderingSystem::BeginRender()
{
    PROFILER_EVENT_CATEGORY("Begin rendering", ProfilerCategory::Rendering);

    UpdateWindowAsNeeded();

    m_renderer->BeginRenderFrame();
}

void RenderingSystem::EndRender()
{
    PROFILER_EVENT_CATEGORY("Flush rendering", ProfilerCategory::Rendering);

    // Draw frame for each camera
    auto cameras = GetSortedCameras();

    for (auto& cameraComponent : cameras)
    {
        m_renderer->BeginCameraRendering(cameraComponent);

        for (RenderLayerIndex i = 0; i < 32; i++)
        {
            m_renderer->RenderLayerOpaque(i, cameraComponent);
            m_renderer->RenderLayerTransparency(i, cameraComponent);
        }

#ifdef RED_DEBUG
        auto* debugComp = m_world->GetWorldComponent<DebugComponent>();
        m_renderer->RenderDebug(cameraComponent, debugComp);
#endif

        m_renderer->EndCameraRendering(cameraComponent);
    }

#ifdef RED_DEBUG
    m_renderer->RenderDebugUI();

    auto* debug = m_world->GetWorldComponent<DebugComponent>();
    debug->ClearDebug();
#endif

    m_renderer->EndRenderFrame();
}

Renderer* RenderingSystem::GetRenderer()
{
    return m_renderer;
}

void RenderingSystem::DrawDebug()
{
    PROFILER_EVENT_CATEGORY("DrawDebug", ProfilerCategory::Rendering);

    auto* debugComp = m_world->GetWorldComponent<DebugComponent>();
    if (debugComp == nullptr)
        return;

    m_world->GetPhysicsWorld()->DrawDebug();
}

void RenderingSystem::UpdateWindowAsNeeded()
{
    auto windowEntities = GetComponents<WindowComponent>();
    auto cameraEntities = GetComponents<CameraComponent>();
    auto* eventComponent = m_world->GetWorldComponent<EventsComponent>();

    for (auto& windowTuple : windowEntities)
    {
        // TODO what about window cvars ?
        auto* windowComp = std::get<1>(windowTuple);

        if (eventComponent->IsWindowResized(windowComp->GetSDLWindow()))
        {
            m_renderer->ReCreateWindow(windowComp);
        }
    }

    for (auto& cameras : cameraEntities)
    {
        auto* cameraComp = std::get<1>(cameras);

        // This is required because the camera could have moved last frame
        cameraComp->UpdateState();
    }
}

Array<CameraComponent*, DoubleLinearArrayAllocator> RenderingSystem::GetSortedCameras()
{
    PROFILER_EVENT_CATEGORY("RenderingSystem::GetSortedCameras", ProfilerCategory::Rendering)

    auto cameraEntities = GetComponents<CameraComponent>();
    Array<CameraComponent*, DoubleLinearArrayAllocator> cameras;
    cameras.resize(cameraEntities.size());
    std::transform(cameraEntities.begin(), cameraEntities.end(), cameras.begin(),
                   [](auto& t) { return std::get<1>(t); });

    std::sort(cameras.begin(), cameras.end(),
              [](const CameraComponent* l, const CameraComponent* r) { return l->Depth() < r->Depth(); });

    return cameras;
}

}  // namespace red

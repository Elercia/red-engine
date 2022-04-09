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

    for (auto* spriteEntity : spriteEntities)
    {
        auto* sprite = spriteEntity->GetComponent<Sprite>();
        if (!sprite->IsValid())
            continue;

        auto* transform = spriteEntity->GetComponent<Transform>();

        sprite->NextFrame();

        // Push this entity to the list of entity to render
        m_renderer->Draw(sprite, transform);
    }

    RenderDebug();
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

        m_renderer->RenderOpaque(cameraComponent);
        m_renderer->RenderTransparency(cameraComponent);

#ifdef RED_DEBUG
        m_renderer->RenderDebug(cameraComponent);
#endif

        m_renderer->EndCameraRendering(cameraComponent);
    }

#ifdef RED_DEBUG
    m_renderer->RenderGlobalDebug();
#endif

    m_renderer->EndRenderFrame();
}

Renderer* RenderingSystem::GetRenderer()
{
    return m_renderer;
}

void RenderingSystem::RenderDebug()
{
    auto* debugComp = m_world->GetWorldComponent<DebugComponent>();

    m_world->GetPhysicsWorld()->DrawDebug();

    // Draw debug information
    for (auto& shape : debugComp->m_frameShapes)
    {
        switch (shape->type)
        {
            case DebugShapeType::CIRCLE:
            {
                auto* circle = static_cast<DebugCircle*>(shape.get());

                m_renderer->DrawDebugCircle(circle->center, circle->radius, circle->color);
            }
            break;
            case DebugShapeType::POLYGON:
            {
                auto* polygon = static_cast<DebugPolygon*>(shape.get());

                m_renderer->DrawDebugLines(polygon->points, polygon->color);
            }
            break;
            case DebugShapeType::SEGMENT:
            {
                auto* segment = static_cast<DebugSegment*>(shape.get());

                m_renderer->DrawDebugLine(segment->point1, segment->point2, segment->color);
            }
            break;
            case DebugShapeType::POINT:
            {
                auto* point = static_cast<DebugPoint*>(shape.get());

                m_renderer->DrawDebugPoint(point->coord, point->color);
            }
            break;
        }
    }

    debugComp->m_frameShapes.clear();
}

void RenderingSystem::UpdateWindowAsNeeded()
{
    auto windowEntities = GetComponents<WindowComponent>();
    auto* eventComponent = m_world->GetWorldComponent<EventsComponent>();

    for (auto* windowEntity : windowEntities)
    {
        // TODO what about window cvars ?
        auto* windowComp = windowEntity->GetComponent<WindowComponent>();

        if (eventComponent->IsWindowResized(windowComp->GetSDLWindow()))
        {
            m_renderer->ReCreateWindow(windowComp);
        }
    }
}

Array<CameraComponent*> RenderingSystem::GetSortedCameras()
{
    auto cameraEntities = GetComponents<CameraComponent>();
    Array<CameraComponent*> cameras;
    cameras.resize(cameraEntities.size());
    std::transform(cameraEntities.begin(), cameraEntities.end(), cameras.begin(),
                   [](Entity* e) { return e->GetComponent<CameraComponent>(); });

    std::sort(cameras.begin(), cameras.end(),
              [](const CameraComponent* l, const CameraComponent* r) { return l->Depth() < r->Depth(); });

    return cameras;
}

}  // namespace red

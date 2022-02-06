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
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Renderer.hpp"

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
    PROFILER_CATEGORY("Update render data", Optick::Category::Rendering)

    UpdateWindowAsNeeded();

    auto spriteEntities = GetComponents<Sprite>();

    for (auto* spriteEntity : spriteEntities)
    {
        auto* sprite = spriteEntity->GetComponent<Sprite>();
        if (!sprite->IsValid())
            continue;

        auto* transform = spriteEntity->GetComponent<Transform>();

        sprite->NextFrame();

        // Push this entity to the list of entity to render
        m_renderer->Render(sprite, transform);
    }
}

void RenderingSystem::BeginRender()
{
    PROFILER_CATEGORY("Begin rendering", Optick::Category::Rendering);

    m_renderer->BeginRenderFrame();
}

void RenderingSystem::EndRender()
{
    PROFILER_CATEGORY("End rendering", Optick::Category::Rendering);

    m_renderer->EndRenderFrame();
}

void RenderingSystem::Render()
{
    PROFILER_CATEGORY("Render", Optick::Category::Rendering)

    auto renderables = GetComponents<Renderable>();

    // Draw frame for each camera
    for (auto& cameraEntity : GetComponents<CameraComponent>())
    {
        auto* cameraComponent = cameraEntity->GetComponent<CameraComponent>();
        m_renderer->BeginCameraRendering(cameraComponent);

        m_renderer->RenderOpaque(cameraComponent);
        m_renderer->RenderTransparency(cameraComponent);
        m_renderer->RenderLights(cameraComponent);

        m_renderer->EndCameraRendering(cameraComponent);
    }
}

Renderer* RenderingSystem::GetRenderer()
{
    return m_renderer;
}

void RenderingSystem::DrawDebug(CameraComponent* camera)
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

                m_renderer->DrawCircle(camera, circle->center, circle->radius, circle->color);
            }
            break;
            case DebugShapeType::POLYGON:
            {
                auto* polygon = static_cast<DebugPolygon*>(shape.get());

                m_renderer->DrawLines(camera, polygon->points, polygon->color);
            }
            break;
            case DebugShapeType::SEGMENT:
            {
                auto* segment = static_cast<DebugSegment*>(shape.get());

                m_renderer->DrawLine(camera, segment->point1, segment->point2, segment->color);
            }
            break;
            case DebugShapeType::POINT:
            {
                auto* point = static_cast<DebugPoint*>(shape.get());

                m_renderer->DrawPoint(camera, point->coord, point->color);
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

    for (auto* entity : windowEntities)
    {
        // TODO check if window as been resized
        // TODO check for fullscreen change
    }
}

}  // namespace red

#include "RedEngine/Rendering/System/RenderingSystem.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

namespace red
{
RenderingSystem::RenderingSystem(World* world) : System(world), m_renderer(nullptr)
{
}

void RenderingSystem::Init()
{
    System::Init();

    auto* window = m_world->CreateWorldEntity("Window")->AddComponent<WindowComponent>();
    window->CreateNewWindow();

    m_renderer = new Renderer;

    m_renderer->InitRenderer(window);
}

void RenderingSystem::Update()
{
    PROFILER_CATEGORY("Update render data", Optick::Category::Rendering)

    /*auto sprites = GetComponents<Sprite>();

for (auto* sprite : sprites)
{
    if (!sprite->IsValid())
            continue;

    sprite->NextFrame();
}*/
}

void RenderingSystem::BeginRender()
{
    m_renderer->BeginRenderFrame();
}

void RenderingSystem::EndRender()
{
    m_renderer->EndRenderFrame();
}

void RenderingSystem::Render()
{
    PROFILER_CATEGORY("Rendering", Optick::Category::Rendering)

    auto renderables = GetComponents<Renderable>();

    // Draw frame for each camera
    for (auto& cameraEntity : GetComponents<CameraComponent>())
    {
        auto* cameraComponent = cameraEntity->GetComponent<CameraComponent>();
        m_renderer->BeginCameraRendering(cameraComponent);

        // Draw each sprite
        for (auto& entity : renderables)
        {
            auto* renderable = entity->GetComponent<Renderable>();
            auto* transform = entity->GetComponent<Transform>();

            m_renderer->Render(cameraComponent, renderable, *transform);
        }

        DrawDebug(cameraComponent);

        m_renderer->EndCameraRendering();
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

}  // namespace red

#include "RedEngine/Rendering/System/RenderingSystem.hpp"

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"

namespace red
{
RenderingSystem::RenderingSystem(World* world) : System(world), m_renderer(nullptr)
{
    RED_LOG_INFO("Adding Rendering system");
}

void RenderingSystem::Init()
{
    System::Init();

    auto* window = GetSingletonEntity()->AddComponent<WindowComponent>();
    window->CreateNewWindow();

    m_renderer = new Renderer;

    m_renderer->InitRenderer(window);
}

void RenderingSystem::Update()
{
    PROFILER_CATEGORY("Rendering", Optick::Category::Rendering)

    m_renderer->BeginRenderFrame();

    // Draw frame for each camera
    for (auto& camera : GetComponents<CameraComponent>())
    {
        auto* cameraComponent = camera->GetComponent<CameraComponent>();
        m_renderer->BeginCameraRendering(cameraComponent);

        // Draw each sprite
        for (auto& entity : GetComponents<Sprite>())
        {
            auto* sprite = entity->GetComponent<Sprite>();
            auto* transform = entity->GetComponent<Transform>();

            if (!sprite->IsValid())
                continue;

            sprite->NextFrame();

            DrawDebug(cameraComponent);

            m_renderer->Render(cameraComponent, sprite, *transform);
        }

        m_renderer->EndCameraRendering();
    }

    m_renderer->EndRenderFrame();
}

void RenderingSystem::PreUpdate()
{
}
void RenderingSystem::PostUpdate()
{
}

red::Renderer* RenderingSystem::GetRenderer()
{
    return m_renderer;
}

void RenderingSystem::DrawDebug(CameraComponent* camera)
{
    auto* debugComp = GetSingletonEntity()->GetComponent<DebugComponent>();

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

    m_world->GetPhysicsWorld()->DrawDebug();
}

}  // namespace red

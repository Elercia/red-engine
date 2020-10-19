#include <RedEngine/Rendering/System/RenderingSystem.hpp>
#include <RedEngine/Core/Components/Component.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Core/Debug/Logger/Logger.hpp>
#include <RedEngine/Core/Debug/Profiler.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Core/Debug/Component/DebugComponent.hpp>

namespace red
{
RenderingSystem::RenderingSystem(World* world)
    : System(world)
    , m_renderingEngine(GetRedSubEngine<RenderingEngine>())
    , m_resourceEngine(GetRedSubEngine<ResourceEngine>())
{
    RED_LOG_INFO("Adding Rendering system");
}

void RenderingSystem::Update()
{
    PROFILER_CATEGORY("Rendering", Optick::Category::Rendering)

    m_renderingEngine->BeginRenderFrame();

    // Draw frame for each camera
    for (auto& camera : GetComponents<CameraComponent>())
    {
        auto* cameraComponent = camera->GetComponent<CameraComponent>();
        m_renderingEngine->BeginCameraRendering(cameraComponent);

        // Draw each sprite
        for (auto& entity : GetComponents<Transform, Sprite>())
        {
            auto* sprite = entity->GetComponent<Sprite>();
            auto* transform = entity->GetComponent<Transform>();

            sprite->NextFrame();

            DrawDebug(cameraComponent);

            m_renderingEngine->Render(cameraComponent, sprite, *transform);
        }

        m_renderingEngine->EndCameraRendering();
    }

    m_renderingEngine->EndRenderFrame();
}

void RenderingSystem::PreUpdate() {}
void RenderingSystem::LateUpdate() {}

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

                m_renderingEngine->DrawCircle(camera, circle->center, circle->radius,
                                              circle->color);
            }
            break;
            case DebugShapeType::POLYGON:
            {
                auto* polygon = static_cast<DebugPolygon*>(shape.get());

                m_renderingEngine->DrawLines(camera, polygon->points, polygon->color);
            }
            break;
            case DebugShapeType::SEGMENT:
            {
                auto* segment = static_cast<DebugSegment*>(shape.get());

                m_renderingEngine->DrawLine(camera, segment->point1, segment->point2,
                                            segment->color);
            }
            break;
            case DebugShapeType::POINT:
            {
                auto* point = static_cast<DebugPoint*>(shape.get());

                m_renderingEngine->DrawPoint(camera, point->coord, point->color);
            }
            break;
        }
    }

    debugComp->m_frameShapes.clear();

    m_world->GetPhysicsWorld()->DrawDebugData();
}

}  // namespace red

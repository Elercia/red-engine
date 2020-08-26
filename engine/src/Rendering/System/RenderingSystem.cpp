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

    auto* debugComp = GetSingletonEntity()->GetComponent<DebugComponent>();

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

            m_renderingEngine->Render(cameraComponent, sprite, *transform);
        }

        // Draw debug information
        for (auto& line : debugComp->m_frameDebugLines)
        {
            m_renderingEngine->DrawLine(cameraComponent, line.first, line.second);
        }

        debugComp->m_frameDebugLines.clear();

        m_renderingEngine->EndCameraRendering();
    }

    m_renderingEngine->EndRenderFrame();
}

void RenderingSystem::PreUpdate() {  }
void RenderingSystem::LateUpdate() {  }

}  // namespace red

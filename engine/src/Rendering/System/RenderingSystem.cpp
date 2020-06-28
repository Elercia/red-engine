#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"
#include "RedEngine/Rendering/Texture2D.hpp"

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

    for (auto& camera : GetComponents<CameraComponent>())
    {
        auto* cameraComponent = camera->GetComponent<CameraComponent>();
        m_renderingEngine->BeginCameraRendering(cameraComponent);

        for (auto& entity : GetComponents<Transform, Sprite>())
        {
            auto* sprite = entity->GetComponent<Sprite>();
            auto* transform = entity->GetComponent<Transform>();

            m_renderingEngine->Render(cameraComponent, sprite, *transform);
        }

        m_renderingEngine->EndCameraRendering();
    }
}

void RenderingSystem::PreUpdate() { m_renderingEngine->BeginRenderFrame(); }
void RenderingSystem::LateUpdate() { m_renderingEngine->EndRenderFrame(); }

}  // namespace red

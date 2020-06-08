#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Debug/Profiler.hpp"
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

    auto& window = m_renderingEngine->GetWindow();
    auto windowInfo = window.GetWindowInfo();

    m_renderingEngine->BeginRenderFrame();

    for (auto& entity : GetComponents<Transform, Sprite>())
    {
        auto* sprite = entity->GetComponent<Sprite>();
        auto* transform = entity->GetComponent<Transform>();

        m_renderingEngine->Render(sprite, *transform);
    }

    m_renderingEngine->EndRenderFrame();
}

void RenderingSystem::Finalise() {}

}  // namespace red

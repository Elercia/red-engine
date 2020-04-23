#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Debug/Profiler.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"
#include "RedEngine/Rendering/Texture.hpp"

namespace red
{
RenderingSystem::RenderingSystem(World* world)
    : System(world)
    , m_renderingEngine(GetRedInstance().GetRenderingEngine())
    , m_resourceEngine(GetRedInstance().GetResourceEngine())
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

    m_renderingEngine->DebugDrawRect();

    m_renderingEngine->EndRenderFrame();
}

void RenderingSystem::Finalise() {}

}  // namespace red

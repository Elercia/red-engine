#include "RedEngine/Rendering/RenderingSystem.hpp"
#include "RedEngine/Rendering/Components/Sprite.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Debug/Profiler.hpp"
#include "RedEngine/Rendering/Window.hpp"

namespace red
{
RenderingSystem::RenderingSystem(World* world)
    : System(world)
    , m_renderingEngine(GetRedSubEngine<RenderingEngine>())
    , m_resourceEngine(GetRedSubEngine<ResourceEngine>())
{
    RED_LOG_INFO("Adding Rendering system");
}

void RenderingSystem::Update(float deltaTime)
{
    PROFILER_CATEGORY("Rendering", Optick::Category::Rendering)

    auto& window = m_renderingEngine->GetWindow();
    auto windowInfo = window.GetWindowInfo();

    m_renderingEngine->BeginRenderFrame();

    for (auto& entity : GetComponents<Sprite>())
    {
        auto* sprite = entity->GetComponent<Sprite>();
        if (sprite->GetLoadedState() == LoadState::STATE_NOT_LOADED)
        {
            m_resourceEngine->ImportSprite(sprite);
        }

        m_renderingEngine->Render(sprite);
    }

    m_renderingEngine->DebugDrawRect();

    m_renderingEngine->EndRenderFrame();
}
void RenderingSystem::Finalise()
{
    for (auto& entity : GetComponents<Sprite>())
    {
        auto* sprite = entity->GetComponent<Sprite>();
        if (sprite->GetLoadedState() == LoadState::STATE_LOADED)
        {
            m_resourceEngine->FreeSprite(sprite);
        }
    }
}

}  // namespace red

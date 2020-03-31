#include "RedEngine/Rendering/RenderingSystem.hpp"

#include "RedEngine/Core/Components/Mesh.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"

namespace red
{
RenderingSystem::RenderingSystem(World* world)
    : System(world), m_renderingEngine(GetRedInstance().GetRenderingEngine())
{
    RED_LOG_INFO("Adding Rendering system");
}

void RenderingSystem::Update(float deltaTime)
{
    auto& window = m_renderingEngine->GetWindow();
    auto windowInfo = window.GetWindowInfo();

    for (auto& entity : GetComponents<Mesh>())
    {
        auto mesh = entity->GetComponent<Mesh>();
        if (mesh->GetLoadedState() == LoadState::NOT_LOADED)
        {
            auto& engine = GetRedInstance();
            engine.GetResourceEngine()->ImportMesh(mesh);
        }
    }
}
}  // namespace red

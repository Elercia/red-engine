#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Core/Application.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"
#include "RedEngine/Core/SubEngine.hpp"
#include "RedEngine/Level/LevelResourceLoader.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"
namespace red
{
Engine& GetEngine()
{
    static Engine s_engine;
    return s_engine;
}

void Engine::Init(const EngineInitDesc& initDesc)
{
    auto& instance = GetEngine();

    instance.m_initDesc = initDesc;
    instance.InitAllSubEngines(initDesc);

    instance.RegisterResourceLoaders(instance.Get<ResourceEngine>());
}

Application& Engine::GetApplication()
{
    if (m_application == nullptr)
    {
        m_application = std::make_unique<Application>();
    }

    return *m_application;
}

void Engine::RegisterResourceLoaders(ResourceEngine* resourceEngine)
{
    RED_ASSERT_S(resourceEngine->RegisterResourceLoader(ResourceType::TEXTURE2D, new TextureResourceLoader));
    RED_ASSERT_S(resourceEngine->RegisterResourceLoader(ResourceType::SPRITE, new SpriteResourceLoader));
    RED_ASSERT_S(resourceEngine->RegisterResourceLoader(ResourceType::LEVEL, new LevelResourceLoader));
}

const red::EngineInitDesc& Engine::GetInitDesc() const { return m_initDesc; }

void Engine::InitAllSubEngines(const EngineInitDesc& initDesc)
{
    std::apply(
        [initDesc](auto&... tupleArgs) {
            ((void) ApplyInit(std::forward<decltype(tupleArgs)>(tupleArgs), initDesc), ...);
        },
        m_subEngines);
}
}  // namespace red

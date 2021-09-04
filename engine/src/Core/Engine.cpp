#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Event/System/EventSystem.hpp"
#include "RedEngine/Core/Time/FrameCounter.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Level/LevelResourceLoader.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Audio/System/AudioSystem.hpp"

namespace red
{
Engine* Engine::s_engine = nullptr;

Engine* Engine::GetInstance()
{
    return s_engine;
}

Engine::Engine() : m_argc(0), m_argv(nullptr), m_world(nullptr) {}

Engine::~Engine() {}

int Engine::MainLoop()
{
    m_world->Init();

    bool continueExec = true;

    FrameCounter fc;

    while (continueExec)
    {
        float deltaTime = fc.Update();

        Time::SetDeltaTime(deltaTime);

        //RED_LOG_DEBUG("FPS {}", 1 / deltaTime);

        continueExec = m_world->Update();

        m_world->Clean();
    }

    return 0;
}

bool Engine::Create()
{
    m_world = new World;

    auto* singletonEntity = m_world->CreateSingletonEntity();

    // TODO Put it inside a resource loader system
    ResourceHolderComponent* resourceHolder = singletonEntity->AddComponent<ResourceHolderComponent>();
    resourceHolder->RegisterResourceLoader(ResourceType::SPRITE, new SpriteResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::TEXTURE2D, new TextureResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::LEVEL, new LevelResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::SOUND, new SoundResourceLoader(m_world));

    m_world->AddSystem<RenderingSystem>();
    m_world->AddSystem<PhysicSystem>();
    m_world->AddSystem<DebugSystem>();
    m_world->AddSystem<EventSystem>();
    m_world->AddSystem<UserInputSystem>();
    m_world->AddSystem<AudioSystem>();

    m_world->Init();

    return true;
}

bool Engine::Destroy()
{
    auto* singletonEntity = m_world->GetSingletonEntity();

    auto* resourceHolder = singletonEntity->GetComponent<ResourceHolderComponent>();

    resourceHolder->RemoveAllLoaders();


    m_world->Finalize();

    delete m_world;

    return true;
}

std::string_view Engine::GetGameName() const
{
    return "RedEngine";
}

}  // namespace red

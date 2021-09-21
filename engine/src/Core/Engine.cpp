#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Audio/System/AudioSystem.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Event/System/EventSystem.hpp"
#include "RedEngine/Core/Time/FrameCounter.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Utils/Random.hpp"

namespace red
{
Engine* Engine::s_engine = nullptr;

Engine* Engine::GetInstance()
{
    return s_engine;
}

Engine::Engine() : m_argc(0), m_argv(nullptr), m_world(nullptr)
{
}

Engine::~Engine()
{
}

int Engine::MainLoop()
{
    m_world->Init();

    bool continueExec = true;

    FrameCounter fc;

    while (continueExec)
    {
        float deltaTime = fc.Update();

        Time::SetDeltaTime(deltaTime);

        // RED_LOG_DEBUG("FPS {}", 1 / deltaTime);

        continueExec = m_world->Update();

        m_world->Clean();
    }

    InternalDestroy();

    return 0;
}

bool Engine::RegisterComponentTypes()
{
    CHECK_RETURN(m_world->RegisterComponentType<Transform>());
    CHECK_RETURN(m_world->RegisterComponentType<DebugComponent>());
    CHECK_RETURN(m_world->RegisterComponentType<EventsComponent>());
    CHECK_RETURN(m_world->RegisterComponentType<UserInputComponent>());
    CHECK_RETURN(m_world->RegisterComponentType<ColliderList>());
    CHECK_RETURN(m_world->RegisterComponentType<PhysicBody>());
    CHECK_RETURN(m_world->RegisterComponentType<Sprite>());
    CHECK_RETURN(m_world->RegisterComponentType<WindowComponent>());
    CHECK_RETURN(m_world->RegisterComponentType<CameraComponent>());
    CHECK_RETURN(m_world->RegisterComponentType<ResourceHolderComponent>());
    CHECK_RETURN(m_world->RegisterComponentType<AudioSource>());
    CHECK_RETURN(m_world->RegisterComponentType<AudioListener>());

    return true;
}

bool Engine::InternalDestroy()
{
    Destroy();

    m_world->Finalize();

    delete m_world;

    return true;
}

bool Engine::InternalCreate()
{
    InitRandomEngine(42);

    m_world = new World;

    RegisterComponentTypes();

    auto* worldEntity = m_world->CreateWorldEntity();

    // TODO Put it inside a resource loader system
    auto* resourceHolder = worldEntity->AddComponent<ResourceHolderComponent>();
    resourceHolder->RegisterResourceLoader(ResourceType::SPRITE, new SpriteResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::TEXTURE2D, new TextureResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::SOUND, new SoundResourceLoader(m_world));

    m_world->AddSystem<RenderingSystem>();
    m_world->AddSystem<PhysicSystem>();
    m_world->AddSystem<DebugSystem>();
    m_world->AddSystem<EventSystem>();
    m_world->AddSystem<UserInputSystem>();
    m_world->AddSystem<AudioSystem>();

    m_world->Init();

    return Create();
}

bool Engine::Destroy()
{
    auto* resourceHolder = m_world->GetWorldComponent<ResourceHolderComponent>();

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

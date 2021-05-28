#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
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
#include "RedEngine/Level/LevelResourceLoader.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"

namespace red
{
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
    m_world = new World;

    RegisterComponentTypes();

    auto* singletonEntity = m_world->CreateSingletonEntity();

    // TODO Put it inside a resource loader system
    auto* resourceHolder = singletonEntity->AddComponent<ResourceHolderComponent>();
    resourceHolder->RegisterResourceLoader(ResourceType::SPRITE, new SpriteResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::TEXTURE2D, new TextureResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::LEVEL, new LevelResourceLoader(m_world));

    m_world->AddSystem<RenderingSystem>();
    m_world->AddSystem<PhysicSystem>();
    m_world->AddSystem<DebugSystem>();
    m_world->AddSystem<EventSystem>();
    m_world->AddSystem<UserInputSystem>();

    m_world->Init();

    return Create();
}

}  // namespace red

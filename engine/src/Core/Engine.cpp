
#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Audio/System/AudioSystem.hpp"
#include "RedEngine/Core/Configuration/CVarManager.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Event/System/EventSystem.hpp"
#include "RedEngine/Core/Time/FrameCounter.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/GeometryResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgramResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Utils/Random.hpp"

#ifdef RED_WINDOWS
#define NOMINMAX 1
#include <debugapi.h>
#include <windows.h>  // For some reason, some include above define some macros that break everything with a #error "No Target Architecture"
#endif

namespace red
{
#ifdef RED_DEBUG
#define DefaultLogLevel LogLevel::LEVEL_DEBUG
#else
#define DefaultLogLevel LogLevel::LEVEL_INFO
#endif

static CVar<bool> s_addStandardOutputLog{"AddStandardOutputlog", "Logger", false};
static CVar<LogLevel> s_logLevel{"LogLevel", "Logger", DefaultLogLevel};

Engine* Engine::s_engine = nullptr;

Engine* Engine::GetInstance()
{
    return s_engine;
}

Engine::Engine() : m_argc(0), m_argv(nullptr), m_world(nullptr), m_frameAllocator(RED_DEFAULT_FRAMEALLOCATOR_SIZE)
{
}

Engine::~Engine()
{
}

void Engine::MainLoop()
{
    bool continueExec = true;

    FrameCounter fc;

    while (continueExec)
    {
        PROFILER_FRAME("MainThread");

        float deltaTime = fc.Update();

        Time::SetDeltaTime(deltaTime);

        continueExec = m_world->Update();

        m_frameAllocator.Swap();
        m_frameAllocator.Reset();
    }
}

bool Engine::RegisterComponentTypes()
{
    PROFILER_EVENT();

    // Rendering
    CheckReturn(m_world->RegisterComponentType<Renderable>());
    CheckReturn(m_world->RegisterComponentType<Sprite>());
    CheckReturn(m_world->RegisterComponentType<WindowComponent>());
    CheckReturn(m_world->RegisterComponentType<CameraComponent>());

    // Debug
    CheckReturn(m_world->RegisterComponentType<DebugComponent>());

    // Inputs
    CheckReturn(m_world->RegisterComponentType<EventsComponent>());
    CheckReturn(m_world->RegisterComponentType<UserInputComponent>());

    // Physics
    CheckReturn(m_world->RegisterComponentType<PhysicBody>());

    // Resources
    CheckReturn(m_world->RegisterComponentType<ResourceHolderComponent>());

    // Audio
    CheckReturn(m_world->RegisterComponentType<AudioSource>());
    CheckReturn(m_world->RegisterComponentType<AudioListener>());

    return true;
}

#if defined(RED_WINDOWS) && defined(RED_DEVBUILD)
static void LogToDebugger(const Logger::LogOoutputInfo& out)
{
    OutputDebugStringA(out.str.c_str());
    OutputDebugStringA("\n");
}
#endif

void Engine::SetupLogger()
{
    PROFILER_EVENT();

    int standarOutputFuncIndex = -1;
    int debugOutputFuncIndex = -1;

#ifdef RED_DEVBUILD
    // Always add standard output when debugging
    standarOutputFuncIndex = GetRedLogger()->AddOutput(Logger::LogToStandardOutputFun);
#endif // RED_DEVBUILD

#if defined(RED_WINDOWS) && defined(RED_DEVBUILD)
    if (IsDebuggerPresent() != 0)
    {
        debugOutputFuncIndex = GetRedLogger()->AddOutput(LogToDebugger);
    }
#endif // defined(RED_WINDOWS) && defined(RED_DEVBUILD)

    if (standarOutputFuncIndex == -1 && s_addStandardOutputLog)
    {
        standarOutputFuncIndex = GetRedLogger()->AddOutput(Logger::LogToStandardOutputFun);
    }

    SetLogLevel(s_logLevel);

    RED_LOG_INFO("Setup logger for output {}, debugger {}", standarOutputFuncIndex != -1, debugOutputFuncIndex != -1);
}

bool Engine::Create()
{
    PROFILER_EVENT();

    CVarManager::LoadConfigFile(Path::Resource("Config.ini"));

    SetupLogger();

    InitSystemInfo();

    InitRandomEngine(42);

    m_scheduler.Init();

    m_world = new World;

    RegisterComponentTypes();

    m_world->Init();

    auto* worldEntity = m_world->CreateWorldEntity("ResourceHolder");

    // TODO Put it inside a resource loader system
    auto* resourceHolder = worldEntity->AddComponent<ResourceHolderComponent>();
    resourceHolder->RegisterResourceLoader(ResourceType::SPRITE, new SpriteResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::TEXTURE2D, new TextureResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::SOUND, new SoundResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::MATERIAL, new MaterialResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::GEOMETRY, new GeometryResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::SHADER_PROGRAM, new ShaderProgramResourceLoader(m_world));

    m_world->AddSystem<RenderingSystem>();
    m_world->AddSystem<SpriteAnimationSystem>();
    m_world->AddSystem<PhysicSystem>();
    m_world->AddSystem<EventSystem>();
    m_world->AddSystem<UserInputSystem>();
    m_world->AddSystem<AudioSystem>();

#ifdef RED_DEVBUILD
    m_world->AddSystem<DebugSystem>();
#endif

    m_world->InitSystems();

    return true;
}

bool Engine::Destroy()
{
    PROFILER_EVENT();

    auto* resourceHolder = m_world->GetWorldComponent<ResourceHolderComponent>();

    resourceHolder->RemoveAllLoaders();

    m_world->Finalize();

    delete m_world;

    m_scheduler.Finalize();

    PROFILER_SHUTDOWN();

    return true;
}

std::string_view Engine::GetGameName() const
{
    return "RedEngine";
}

DoubleLinearAllocator& Engine::GetFrameAllocator()
{
    return m_frameAllocator;
}

ThreadScheduler& Engine::GetScheduler()
{
    return m_scheduler;
}

}  // namespace red

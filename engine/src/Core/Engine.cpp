
#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Audio/Resource/SoundResourceLoader.hpp"
#include "RedEngine/Core/Configuration/CVarManager.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Time/FrameCounter.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Renderable.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/FontResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/GeometryResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/MaterialResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/ShaderProgramResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/SpriteResourceLoader.hpp"
#include "RedEngine/Rendering/Resource/TextureResourceLoader.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Utils/Random.hpp"
#include "RedEngine/Utils/SystemInfo.hpp"

#ifdef RED_WINDOWS
#define NOMINMAX 1
#include <windows.h>
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

Engine::Engine() : m_argc(0), m_argv(nullptr), m_world(nullptr), m_frameAllocator(nullptr)
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

        for (int i = 0; i < m_scheduler.GetWorkerCount(); i++)
        {
            m_frameAllocator[i].Swap();
        }
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
#endif  // RED_DEVBUILD

#if defined(RED_WINDOWS) && defined(RED_DEVBUILD)
    if (IsDebuggerPresent() != 0)
    {
        debugOutputFuncIndex = GetRedLogger()->AddOutput(LogToDebugger);
    }
#endif  // defined(RED_WINDOWS) && defined(RED_DEVBUILD)

    if (standarOutputFuncIndex == -1 && s_addStandardOutputLog)
    {
        standarOutputFuncIndex = GetRedLogger()->AddOutput(Logger::LogToStandardOutputFun);
    }

    SetLogLevel(s_logLevel);

    RED_LOG_INFO("Setup logger for output {}, debugger {}", standarOutputFuncIndex != -1, debugOutputFuncIndex != -1);
}

void Engine::InitAllocator()
{
    auto workerCount = m_scheduler.GetWorkerCount();
    m_frameAllocator = (DoubleLinearAllocator*) red_malloc(workerCount * sizeof(DoubleLinearAllocator));

    for (int i = 0; i < workerCount; i++)
    {
        new (m_frameAllocator + i) DoubleLinearAllocator(RED_DEFAULT_FRAMEALLOCATOR_SIZE);
    }
}

bool Engine::Create()
{
    PROFILER_EVENT();

    CVarManager::LoadConfigFile(Path::Resource("Config.ini"));

    SetupLogger();

    InitSystemInfo();

    InitRandomEngine(42);

    m_scheduler.Init();

    InitAllocator();

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
    resourceHolder->RegisterResourceLoader(ResourceType::FONT, new FontResourceLoader(m_world));
    resourceHolder->RegisterResourceLoader(ResourceType::SHADER_PROGRAM, new ShaderProgramResourceLoader(m_world));

    m_world->BuildExecutionGraph();
    m_world->InitSystems();  // TODO Remove this init systems call and find a way to have "InitSystems" resposible

    return true;
}

bool Engine::Destroy()
{
    PROFILER_EVENT();

    auto* resourceHolder = m_world->GetWorldComponent<ResourceHolderComponent>();

    resourceHolder->RemoveAllLoaders();

    m_world->Finalize();

    delete m_world;

    red_free(m_frameAllocator);

    m_scheduler.Finalize();

    PROFILER_SHUTDOWN();

    return true;
}

std::string_view Engine::GetGameName() const
{
    return "RedEngine";
}

DoubleLinearAllocator& Engine::GetThreadFrameAllocator(int threadIndex)
{
    return m_frameAllocator[threadIndex];
}

ThreadScheduler& Engine::GetScheduler()
{
    return m_scheduler;
}

}  // namespace red

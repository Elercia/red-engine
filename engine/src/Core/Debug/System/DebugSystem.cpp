
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

#include <Box2D/b2_draw.h>
#include <Box2D/box2d.h>

namespace red
{
DebugSystem::DebugSystem(World* world) : System(world) {}

void DebugSystem::Init()
{
    System::Init();
    GetSingletonEntity()->AddComponent<DebugComponent>();
}

void DebugSystem::Update()
{
    PROFILER_CATEGORY("Debug", Optick::Category::Debug);

    auto* events = GetComponent<EventsComponent>();
    auto* debugComp = GetComponent<DebugComponent>();

    if (events->GetKeyDown(KeyCodes::KEY_F1))
    {
        if (debugComp->m_physicsDebugDrawer == nullptr)
        {
            debugComp->m_physicsDebugDrawer = std::make_unique<PhysicsDebugDrawer>(debugComp);
            debugComp->m_physicsDebugDrawer->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit |
                                                      b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
        }
        else
        {
            debugComp->m_physicsDebugDrawer.release();
        }

        m_world->GetPhysicsWorld()->SetDebugDrawer(debugComp->m_physicsDebugDrawer.get());
    }

    if (events->GetKeyDown(KeyCodes::KEY_F2))
    {
        CVar<FullScreenMode::Enum> fullscreen{"fullscreen_mode", "window", FullScreenMode::WINDOWED};

        fullscreen.ChangeValue(fullscreen.GetValue() == FullScreenMode::WINDOWED ? FullScreenMode::FULLSCREEN
                                                                                 : FullScreenMode::WINDOWED);
    }

    if (events->GetKeyDown(KeyCodes::KEY_F5))
    {
        Time::SetTimeScale(Time::TimeScale() + 0.1F);
    }

    if (events->GetKeyDown(KeyCodes::KEY_F6))
    {
        Time::SetTimeScale(Time::TimeScale() - 0.1F);
    }

    // TODO add the management of the in-game console
}
}  // namespace red

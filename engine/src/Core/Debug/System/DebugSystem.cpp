
#include <RedEngine/Core/Debug/System/DebugSystem.hpp>
#include <RedEngine/Core/Debug/Component/DebugComponent.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <RedEngine/Core/Debug/Profiler.hpp>

#include "Box2D/Common/b2Draw.h"
#include "Box2D/Box2D.h"

namespace red
{
DebugSystem::DebugSystem(World* world)
    : System(world), m_renderingEngine(GetRedSubEngine<RenderingEngine>())
{
}

void DebugSystem::LateUpdate()
{
    PROFILER_CATEGORY("Debug", Optick::Category::Debug);

    auto* eventSystem = GetRedSubEngine<EventSystem>();
    auto* debugComp = GetSingletonEntity()->GetComponent<DebugComponent>();

    if (eventSystem->GetKeyDown(KeyCodes::KEY_F1))
    {
        if (debugComp->m_physicsDebugDrawer == nullptr)
        {
            debugComp->m_physicsDebugDrawer = std::make_unique<PhysicsDebugDrawer>(debugComp);
            debugComp->m_physicsDebugDrawer->SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit |
                                                      b2Draw::e_aabbBit | b2Draw::e_pairBit |
                                                      b2Draw::e_centerOfMassBit);
        }
        else
        {
            debugComp->m_physicsDebugDrawer.release();
        }

        m_world->GetPhysicsWorld()->SetDebugDraw(
            reinterpret_cast<b2Draw*>(debugComp->m_physicsDebugDrawer.get()));
    }

    if (eventSystem->GetKeyDown(KeyCodes::KEY_F2))
    {
        CVar<FullScreenMode::Enum> fullscreen{"fullscreen_mode", "window",
                                              FullScreenMode::WINDOWED};

        fullscreen.ChangeValue(fullscreen.GetValue() == FullScreenMode::WINDOWED
                                   ? FullScreenMode::FULLSCREEN
                                   : FullScreenMode::WINDOWED);
    }

    if (eventSystem->GetKeyDown(KeyCodes::KEY_F5))
    {
        Time::SetTimeScale(Time::TimeScale() + 0.1F);
    }

    if (eventSystem->GetKeyDown(KeyCodes::KEY_F6))
    {
        Time::SetTimeScale(Time::TimeScale() - 0.1F);
    }

    // TODO add the management of the in-game console
}
}  // namespace red

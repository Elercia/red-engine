#include "RedEngine/Rendering/System/SpriteAnimationSystem.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Renderer.hpp"

#include <SDL2/SDL.h>
#include <algorithm>

namespace red
{
SpriteAnimationSystem::SpriteAnimationSystem(World* world) : System(world)
{
}

void SpriteAnimationSystem::Update()
{
    PROFILER_EVENT_CATEGORY("Update sprites", ProfilerCategory::Rendering);

    auto spriteEntities = QueryComponents();

    for (auto& comps : spriteEntities)
    {
        auto sprite = std::get<1>(comps);
        if (!sprite->IsValid())
            continue;

        sprite->NextFrame();
    }
}
}  // namespace red

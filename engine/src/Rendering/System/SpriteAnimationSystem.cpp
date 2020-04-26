
#include <RedEngine/Rendering/System/SpriteAnimationSystem.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

namespace red
{
SpriteAnimationSystem::SpriteAnimationSystem(red::World* world) : System(world)
{
    RED_LOG_INFO("Adding SpriteAnimation system");
}

void SpriteAnimationSystem::Update()
{
    auto entities = GetComponents<Sprite>();

    for (auto& entity : entities)
    {
        auto* spriteComponent = entity->GetComponent<Sprite>();
    }
}

void SpriteAnimationSystem::Finalise() {}

}  // namespace red
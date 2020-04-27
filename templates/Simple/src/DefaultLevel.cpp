#include "DefaultLevel.hpp"
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/System/RenderingSystem.hpp>

void DefaultLevel::Init(red::World& world)
{
    auto texture = red::ResourceEngine::LoadTexture("resources/fantom.bmp");

    auto* entity = world.CreateEntity();
    entity->AddComponent<red::Sprite>(texture);
    entity->AddComponent<red::Transform>(300, 100);

    world.AddSystem<red::RenderingSystem>();
}

void DefaultLevel::Finalize() {}

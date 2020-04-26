#include "DefaultLevel.hpp"
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

void DefaultLevel::Init()
{
    CreateWorld();

    auto texture = red::ResourceEngine::LoadTexture("resources/fantom.bmp");

    auto* entity = m_world->CreateEntity();
    entity->AddComponent<red::Sprite>(texture);
    entity->AddComponent<red::Transform>(300, 100);
}

void DefaultLevel::Finalize() {}

#include "GameControlSystem.hpp"

#include "box2d/b2_body.h"

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Math/Vector.hpp"

using namespace red;

GameControlSystem::GameControlSystem(red::World* world, red::Entity* paddleOne, red::Entity* paddleTwo)
    : red::System(world), m_paddleOne(paddleOne), m_paddleTwo(paddleTwo)
{
}

void GameControlSystem::Update()
{
    constexpr float velocity = 300.F;

    auto* userInputComponent = m_world->GetWorldComponent<UserInputComponent>();
    auto& paddleOnePos = m_paddleOne->GetComponent<Transform>()->GetPosition();
    auto& paddleTwoPos = m_paddleTwo->GetComponent<Transform>()->GetPosition();

    if (userInputComponent->GetKey("1moveDown"))
    {
        paddleOnePos.y += velocity * red::Time::DeltaTime();
    }
    else if (userInputComponent->GetKey("1moveUp"))
    {
        paddleOnePos.y -= velocity * red::Time::DeltaTime();
    }

    if (userInputComponent->GetKey("2moveDown"))
    {
        paddleTwoPos.y += velocity * red::Time::DeltaTime();
    }
    else if (userInputComponent->GetKey("2moveUp"))
    {
        paddleTwoPos.y -= velocity * red::Time::DeltaTime();
    }

    KeepInBound(paddleOnePos);
    KeepInBound(paddleTwoPos);
}

void GameControlSystem::KeepInBound(red::Vector2& pos)
{
    if (pos.y < 0)
        pos.y = 0;
    if (pos.y + 100.F > 600)
        pos.y = static_cast<float>(600 - 100);
}

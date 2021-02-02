#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Core/Components/Transform.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/Window.hpp"

#include "GameControlSystem.hpp"

GameControlSystem::GameControlSystem(red::World* world, red::Entity* paddleOne,
                                     red::Entity* paddleTwo)
    : red::System(world), m_paddleOne(paddleOne), m_paddleTwo(paddleTwo)
{
}

void GameControlSystem::Update()
{
    constexpr float velocity = 300.F;
    using namespace red;

    auto* userInputComponent = GetSingletonEntity()->AddComponent<UserInputComponent>();
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
    auto info = red::GetSubEngine<red::RenderingEngine>()->GetWindow().GetWindowInfo();

    if (pos.y < 0)
        pos.y = 0;
    if (pos.y + 100.F > static_cast<float>(info.height))
        pos.y = static_cast<float>(info.height - 100);
}

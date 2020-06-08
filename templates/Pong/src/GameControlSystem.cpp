#include <RedEngine/Input/Component/UserInput.hpp>
#include <RedEngine/Core/Components/Transform.hpp>
#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Rendering/RenderingEngine.hpp>
#include <RedEngine/Rendering/Window.hpp>
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

    auto* userInputComponent = GetSingletonEntity().GetComponent<UserInputComponent>();
    auto& paddleOnePos = m_paddleOne->GetComponent<Transform>()->GetPosition();
    auto& paddleTwoPos = m_paddleTwo->GetComponent<Transform>()->GetPosition();

    if (userInputComponent->GetKey("1moveDown"))
    {
        paddleOnePos.m_y += velocity * Time::DeltaTime();
    }
    else if (userInputComponent->GetKey("1moveUp"))
    {
        paddleOnePos.m_y -= velocity * Time::DeltaTime();
    }

    if (userInputComponent->GetKey("2moveDown"))
    {
        paddleTwoPos.m_y += velocity * Time::DeltaTime();
    }
    else if (userInputComponent->GetKey("2moveUp"))
    {
        paddleTwoPos.m_y -= velocity * Time::DeltaTime();
    }

    KeepInBound(paddleOnePos);
    KeepInBound(paddleTwoPos);
}

void GameControlSystem::KeepInBound(red::Vector2& pos)
{
    auto info = red::GetRedSubEngine<red::RenderingEngine>()->GetWindow().GetWindowInfo();

    if (pos.m_y < 0)
        pos.m_y = 0;
    if (pos.m_y + 100.F > static_cast<float>(info.height))
        pos.m_y = static_cast<float>(info.height - 100);
}

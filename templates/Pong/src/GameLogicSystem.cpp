#include <RedEngine/Core/Components/Transform.hpp>
#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <RedEngine/Math/Math.hpp>

#include "GameLogicSystem.hpp"
#include "BallComponent.hpp"
#include "ScoreComponent.hpp"

GameLogicSystem::GameLogicSystem(red::World* world, red::Entity* paddleOne, red::Entity* paddleTwo,
                                 red::Entity* ball)
    : red::System(world), m_paddleOne(paddleOne), m_paddleTwo(paddleTwo), m_ball(ball)
{
}

void GameLogicSystem::Update()
{
    using namespace red;

    auto* ballTransform = m_ball->GetComponent<Transform>();
    auto* ballComponent = m_ball->GetComponent<BallComponent>();

    auto* paddleOneTransform = m_paddleOne->GetComponent<Transform>();
    auto* paddleTwoTransform = m_paddleTwo->GetComponent<Transform>();

    auto& ballPos = ballTransform->GetPosition();
    auto deltaTime = red::Time::DeltaTime();
    ballPos.x += ballComponent->m_velocity.x * deltaTime;
    ballPos.y += ballComponent->m_velocity.y * deltaTime;

    auto info = GetRedSubEngine<RenderingEngine>()->GetWindow().GetWindowInfo();

    if (ballPos.y < (0 + 30.F / 2.F) || ballPos.y > (static_cast<float>(info.height) - 30.F / 2.F))
        ballComponent->m_velocity.y *= -1;  // TODO smooth the bouncing with the ball size

    DebugDrawLine(ballPos, ballPos + ballComponent->m_velocity * 100.F);

    BounceOnPaddles(paddleOneTransform, paddleTwoTransform, ballPos, ballComponent);

    CheckPoints(ballPos, info);
}

void GameLogicSystem::CheckPoints(red::Vector2& ballPos, const red::WindowInfo& info)
{
    auto* score = GetSingletonEntity()->GetComponent<ScoreComponent>();
    bool scored = false;

    if (ballPos.x < 0)
    {
        std::get<0>(score->m_scores)++;
        scored = true;
    }
    else if (ballPos.x > info.width)
    {
        std::get<1>(score->m_scores)++;
        scored = true;
    }

    if (scored)
    {
        ballPos = {info.width / 2.F, info.height / 2.F};
    }
}

void GameLogicSystem::BounceOnPaddles(const red::Transform* paddleOneTransform,
                                      const red::Transform* paddleTwoTransform,
                                      red::Vector2& ballPos, BallComponent* ballComponent)
{
    const auto& paddleOnePos = paddleOneTransform->GetPosition();
    const auto& paddleTwoPos = paddleTwoTransform->GetPosition();

    if (ballPos.x < paddleOnePos.x &&
        red::Math::Between(ballPos.y, paddleOnePos.y, paddleOnePos.y + 100))
    {
        ballComponent->m_velocity.x *= -1;
    }

    if (ballPos.x > paddleTwoPos.x &&
        red::Math::Between(ballPos.y, paddleTwoPos.y, paddleTwoPos.y + 100))
    {
        ballComponent->m_velocity.x *= -1;
    }
}

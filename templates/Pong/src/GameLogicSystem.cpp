#include "RedEngine/Core/Components/Transform.hpp"
#include "RedEngine/Core/Time/Time.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Rendering/Window.hpp"
#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"

#include "GameLogicSystem.hpp"
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

    auto& ballPos = ballTransform->GetPosition();

    CheckPoints(ballPos);
}

void GameLogicSystem::Init()
{
    using namespace red;

    auto* body = m_ball->GetComponent<PhysicBody>()->GetBody();

    body->SetLinearVelocity({10.f, 1.f});
}

void GameLogicSystem::CheckPoints(red::Vector2& ballPos)
{
    auto info = red::Window::GetWindow().GetWindowInfo();

    auto* e = GetComponents<ScoreComponent>()[0];  // TODO Create a find by entity name
    auto* score = e->GetComponent<ScoreComponent>();
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
        ballPos = {info.width / 2.f, info.height / 2.f};
    }
}

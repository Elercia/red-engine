#include "GameLogicSystem.hpp"

#include "ScoreComponent.hpp"

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"

using namespace red;

GameLogicSystem::GameLogicSystem(red::World* world, red::Entity* paddleOne, red::Entity* paddleTwo, red::Entity* ball)
    : red::System(world), m_paddleOne(paddleOne), m_paddleTwo(paddleTwo), m_ball(ball)
{
}

void GameLogicSystem::Update()
{
    auto* ballTransform = m_ball->GetComponent<Transform>();

    auto& ballPos = ballTransform->GetPosition();

    CheckPoints(ballPos);
}

void GameLogicSystem::Init()
{
    System::Init();

    auto* body = m_ball->GetComponent<PhysicBody>()->GetBody();

    body->SetLinearVelocity({10.f, 10.f});
    body->SetBullet(true);
}

void GameLogicSystem::CheckPoints(red::Vector2& ballPos)
{
    auto info = GetComponent<red::WindowComponent>()->GetWindowInfo();

    auto scores = GetComponents<ScoreComponent>();
    bool scored = false;

    if (scores.empty() || scores.size() > 1)
        return;

    auto* score = scores[0]->GetComponent<ScoreComponent>();

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

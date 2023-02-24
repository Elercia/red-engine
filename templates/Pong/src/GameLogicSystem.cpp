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

    auto& ballPos = ballTransform->GetLocalPosition();

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
    auto info = m_world->GetWorldComponent<red::WindowComponent>()->GetWindowInfo();

    auto scores = GetComponents<ScoreComponent>();
    bool scored = false;

    if (scores.empty() || scores.size() > 1)
        return;

    auto* score = std::get<1>(scores[0]);

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
        ballPos = {(float)info.width / 2.f, (float)info.height / 2.f};
    }
}

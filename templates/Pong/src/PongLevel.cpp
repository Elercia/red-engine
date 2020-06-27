#include "PongLevel.hpp"
#include "GameLogicSystem.hpp"
#include "BallComponent.hpp"
#include "ScoreComponent.hpp"
#include "GameControlSystem.hpp"

#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <RedEngine/Rendering/Component/CameraComponent.hpp>

void PongLevel::Init()
{
    auto ballTexture = red::ResourceEngine::LoadTexture("resources/ball.png");
    ballTexture->ChangeTextureSize({30, 30});
    auto paddleTexture = red::ResourceEngine::LoadTexture("resources/paddle.png");
    paddleTexture->ChangeTextureSize({30, 100});

    auto& window = red::Window::GetWindow();
    auto info = window.GetWindowInfo();

    float paddlePosHeight =
        (info.height / 2.F) - (static_cast<float>(paddleTexture->GetTextureSize().y) / 2.F);

    red::Vector2 center{info.width / 2.F, info.height / 2.F};

    auto* ball = m_world->CreateEntity("Ball");
    ball->AddComponent<red::Sprite>(ballTexture);
    ball->AddComponent<red::Transform>(center);
    ball->AddComponent<BallComponent>(red::Vector2{100.F, 100.F});

    auto* paddleOne = m_world->CreateEntity("PaddleTwo");
    paddleOne->AddComponent<red::Sprite>(paddleTexture);
    paddleOne->AddComponent<red::Transform>(100.F, paddlePosHeight);

    auto* paddleTwo = m_world->CreateEntity("PaddleOne");
    paddleTwo->AddComponent<red::Sprite>(paddleTexture);
    paddleTwo->AddComponent<red::Transform>(
        info.width - 100.F - (static_cast<float>(paddleTexture->GetTextureSize().x) / 2.F),
        paddlePosHeight);

    auto& singletonEntity = m_world->GetSingletonEntity();
    singletonEntity.AddComponent<ScoreComponent>();
    singletonEntity.AddComponent<red::CameraComponent>(center);

    m_world->AddSystem<GameLogicSystem>(paddleOne, paddleTwo, ball);
    m_world->AddSystem<GameControlSystem>(paddleOne, paddleTwo);
}

void PongLevel::Finalize()
{
    m_world->RemoveSystem<GameLogicSystem>();
    m_world->RemoveSystem<GameControlSystem>();
}

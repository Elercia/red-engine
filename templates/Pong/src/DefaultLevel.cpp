#include "DefaultLevel.hpp"
#include "GameLogicSystem.hpp"
#include "BallComponent.hpp"
#include "ScoreComponent.hpp"
#include "GameControlSystem.hpp"
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Rendering/Texture2D.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>
#include <RedEngine/Rendering/System/RenderingSystem.hpp>
#include <RedEngine/Input/System/UserInputSystem.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Rendering/Window.hpp>

#include <map>

void DefaultLevel::Init(red::World& world)
{
    auto ballTexture = red::ResourceEngine::LoadTexture("resources/ball.png");
    ballTexture->ChangeTextureSize({30, 30});
    auto paddleTexture = red::ResourceEngine::LoadTexture("resources/paddle.png");
    paddleTexture->ChangeTextureSize({30, 100});

    auto& window = red::GetRedSubEngine<red::RenderingEngine>()->GetWindow();
    auto info = window.GetWindowInfo();

    float paddlePosHeight =
        (info.height / 2.F) - (static_cast<float>(paddleTexture->GetTextureSize().y) / 2.F);

    auto* ball = world.CreateEntity("Ball");
    ball->AddComponent<red::Sprite>(ballTexture);
    ball->AddComponent<red::Transform>(info.width / 2.F, info.height / 2.F);
    ball->AddComponent<BallComponent>(red::Vector2{100.F, 100.F});

    auto* paddleOne = world.CreateEntity("PaddleTwo");
    paddleOne->AddComponent<red::Sprite>(paddleTexture);
    paddleOne->AddComponent<red::Transform>(100.F, paddlePosHeight);

    auto* paddleTwo = world.CreateEntity("PaddleOne");
    paddleTwo->AddComponent<red::Sprite>(paddleTexture);
    paddleTwo->AddComponent<red::Transform>(
        info.width - 100.F - (static_cast<float>(paddleTexture->GetTextureSize().x) / 2.F),
        paddlePosHeight);

    auto& singletonEntity = world.GetSingletonEntity();
    singletonEntity.AddComponent<ScoreComponent>();

    world.AddSystem<red::UserInputSystem>();
    world.AddSystem<red::RenderingSystem>();
    world.AddSystem<GameLogicSystem>(paddleOne, paddleTwo, ball);
    world.AddSystem<GameControlSystem>(paddleOne, paddleTwo);
}

void DefaultLevel::Finalize(red::World& world) { world.RemoveSystem<GameLogicSystem>(); }

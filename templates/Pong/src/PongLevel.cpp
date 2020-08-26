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
#include <RedEngine/Input/System/UserInputSystem.hpp>
#include <RedEngine/Rendering/System/RenderingSystem.hpp>
#include <RedEngine/Physics/System/PhysicsSystem.hpp>
#include <RedEngine/Core/Debug/System/DebugSystem.hpp>

void PongLevel::Init()
{
    m_world->AddSystem<red::UserInputSystem>();
    m_world->AddSystem<red::RenderingSystem>();
    m_world->AddSystem<red::PhysicSystem>();
    m_world->AddSystem<red::DebugSystem>();

    auto& window = red::Window::GetWindow();
    auto info = window.GetWindowInfo();

    float paddlePosHeight = (info.height / 2.F) - (100.F / 2.F);

    red::Vector2 center{info.width / 2.F, info.height / 2.F};

    auto* ball = CreateEntity("Ball");
    ball->AddComponent<red::Sprite>("ball");
    ball->AddComponent<red::Transform>(center);
    ball->AddComponent<BallComponent>(red::Vector2{100.F, 100.F});

    auto* paddleOne = CreateEntity("PaddleTwo");
    paddleOne->AddComponent<red::Sprite>("paddle");
    paddleOne->AddComponent<red::Transform>(100.F, paddlePosHeight);

    auto* paddleTwo = CreateEntity("PaddleOne");
    paddleTwo->AddComponent<red::Sprite>("paddle");
    paddleTwo->AddComponent<red::Transform>(info.width - 100.F - (30.F / 2.F), paddlePosHeight);

    auto* singletonEntity = m_world->GetSingletonEntity();
    singletonEntity->AddComponent<ScoreComponent>();
    singletonEntity->AddComponent<red::CameraComponent>(center);

    m_world->AddSystem<GameLogicSystem>(paddleOne, paddleTwo, ball);
    m_world->AddSystem<GameControlSystem>(paddleOne, paddleTwo);
}

void PongLevel::Finalize()
{
    m_world->RemoveSystem<GameLogicSystem>();
    m_world->RemoveSystem<GameControlSystem>();
}

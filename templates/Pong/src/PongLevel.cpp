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
#include <RedEngine/Physics/Components/PhysicBody.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Physics/Components/Collider.hpp>

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
    ball->GetComponent<red::Transform>()->SetPosition(center);
    ball->AddComponent<BallComponent>(red::Vector2{100.F, 100.F});
    red::PhysicBodyCreationDesc desc = {red::PhysicsBodyType::DYNAMIC_BODY};
    ball->AddComponent<red::PhysicBody>(desc);
    ball->AddComponent<red::ColliderList>()->AddCircleCollider({false, {5.F, 5.F}, 10.F});

    auto* paddleOne = CreateEntity("PaddleTwo");
    paddleOne->AddComponent<red::Sprite>("paddle");
    paddleOne->GetComponent<red::Transform>()->SetPosition({100.F, paddlePosHeight});

    auto* paddleTwo = CreateEntity("PaddleOne");
    paddleTwo->AddComponent<red::Sprite>("paddle");
    paddleTwo->GetComponent<red::Transform>()->SetPosition(
        {info.width - 100.F - (30.F / 2.F), paddlePosHeight});

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

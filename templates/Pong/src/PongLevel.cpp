#include "PongLevel.hpp"
#include "GameLogicSystem.hpp"
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
    auto& window = red::Window::GetWindow();
    auto info = window.GetWindowInfo();

    float paddlePosHeight = (info.height / 2.F) - (100.F / 2.F);

    red::Vector2 center{info.width / 2.F, info.height / 2.F};

    auto* ball = CreateEntity("Ball");
    ball->AddComponent<red::Sprite>("ball");
    ball->GetComponent<red::Transform>()->SetPosition(center);

    red::PhysicBodyCreationDesc ballBodyDesc = {red::PhysicsBodyType::DYNAMIC_BODY};
    ball->AddComponent<red::PhysicBody>(ballBodyDesc);
    ball->AddComponent<red::ColliderList>()->AddCircleCollider({false, {5.F, 5.F}, 5.F});

    red::PhysicBodyCreationDesc paddleBodyDesc = {red::PhysicsBodyType::KINEMATIC_BODY};
    red::PolygonColliderDesc paddleColliderDesc = {false, {{0, 0}, {30, 0}, {30, 100}, {0, 100}}};

    auto* paddleOne = CreateEntity("PaddleOne");
    paddleOne->AddComponent<red::Sprite>("paddle");
    paddleOne->GetComponent<red::Transform>()->SetPosition({100.F, paddlePosHeight});

    paddleOne->AddComponent<red::PhysicBody>(paddleBodyDesc);
    paddleOne->AddComponent<red::ColliderList>()->AddPolygonCollider(paddleColliderDesc);

    auto* paddleTwo = CreateEntity("PaddleTwo");
    paddleTwo->AddComponent<red::Sprite>("paddle");
    paddleTwo->GetComponent<red::Transform>()->SetPosition(
        {info.width - 100.F - (30.F / 2.F), paddlePosHeight});

    paddleTwo->AddComponent<red::PhysicBody>(paddleBodyDesc);
    paddleTwo->AddComponent<red::ColliderList>()->AddPolygonCollider(paddleColliderDesc);

    auto* manager = CreateEntity("Manager");
    manager->AddComponent<ScoreComponent>();
    manager->AddComponent<red::CameraComponent>(center);

    red::PhysicBodyCreationDesc wallBodyDesc = {red::PhysicsBodyType::KINEMATIC_BODY};

    auto* wallUp = CreateEntity("Wall Up");
    auto* wallDown = CreateEntity("Wall Dawn");

    wallUp->AddComponent<red::PhysicBody>(wallBodyDesc);
    wallDown->AddComponent<red::PhysicBody>(wallBodyDesc);

    wallUp->AddComponent<red::ColliderList>()->AddEdgeCollider(
        {false, {0.f, 0.f}, {0.f, (float) info.width}});
    wallDown->AddComponent<red::ColliderList>()->AddEdgeCollider(
        {false, {(float) info.height, 0.f}, {(float) info.height, (float) info.width}});

    m_world->AddSystem<red::UserInputSystem>();
    m_world->AddSystem<red::RenderingSystem>();
    m_world->AddSystem<red::PhysicSystem>();
    m_world->AddSystem<red::DebugSystem>();
    m_world->AddSystem<GameLogicSystem>(paddleOne, paddleTwo, ball);
    m_world->AddSystem<GameControlSystem>(paddleOne, paddleTwo);
}

void PongLevel::Finalize()
{
    m_world->RemoveSystem<GameLogicSystem>();
    m_world->RemoveSystem<GameControlSystem>();
}

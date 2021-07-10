#include "PongLevel.hpp"

#include "GameControlSystem.hpp"
#include "GameLogicSystem.hpp"
#include "ScoreComponent.hpp"

#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Audio/AudioEvent.hpp"

void PongLevel::Init()
{
    auto* window = m_world->GetSingletonComponent<red::WindowComponent>();
    auto info = window->GetWindowInfo();

    float paddlePosHeight = (info.height / 2.F) - (100.F / 2.F);

    red::Vector2 center{info.width / 2.F, info.height / 2.F};

    const auto onCollision = [](const red::CollisionInfo& collisionInfo) {
        auto force = red::Vector2(1000.f, 1000.f);
        collisionInfo.firstPhysicBody->GetOwner()->GetComponent<red::AudioSource>()->Play();
    };

    const float ballSize = 30.f;

    red::PhysicBodyCreationDesc ballBodyDesc = {red::PhysicsBodyType::DYNAMIC_BODY};
    red::CircleColliderDesc ballColliderDesc;
    ballColliderDesc.isTrigger = false;
    ballColliderDesc.center = {ballSize / 2.f, ballSize / 2.f};
    ballColliderDesc.radius = ballSize / 2.f;
    ballColliderDesc.restitution = 1.f;

    red::PhysicBodyCreationDesc paddleBodyDesc = {red::PhysicsBodyType::KINEMATIC_BODY};
    red::PolygonColliderDesc paddleColliderDesc;
    paddleColliderDesc.isTrigger = false;
    paddleColliderDesc.points = {{0, 0}, {30, 0}, {30, 100}, {0, 100}};
    paddleColliderDesc.restitution = 1.f;

    red::SoundDesc ballbounding;
    ballbounding.name = "ball_bouncing";

    auto* ball = CreateEntity("Ball");
    ball->AddComponent<red::Sprite>("ball");
    ball->GetComponent<red::Transform>()->SetPosition(center);
    auto* ballPhysicBody = ball->AddComponent<red::PhysicBody>(ballBodyDesc);
    ball->AddComponent<red::ColliderList>()->AddCircleCollider(ballColliderDesc);
    ball->AddComponent<red::AudioSource>(ballbounding);

    auto slot = ballPhysicBody->m_collisionSignal.Connect(onCollision);

    auto* paddleOne = CreateEntity("PaddleOne");
    paddleOne->AddComponent<red::Sprite>("paddle");
    paddleOne->GetComponent<red::Transform>()->SetPosition({100.F, paddlePosHeight});

    paddleOne->AddComponent<red::PhysicBody>(paddleBodyDesc);
    paddleOne->AddComponent<red::ColliderList>()->AddPolygonCollider(paddleColliderDesc);

    auto* paddleTwo = CreateEntity("PaddleTwo");
    paddleTwo->AddComponent<red::Sprite>("paddle");
    paddleTwo->GetComponent<red::Transform>()->SetPosition(
        red::Vector2(info.width - 100.F - (30.F / 2.F), paddlePosHeight));

    paddleTwo->AddComponent<red::PhysicBody>(paddleBodyDesc);
    paddleTwo->AddComponent<red::ColliderList>()->AddPolygonCollider(paddleColliderDesc);

    auto* manager = m_world->GetSingletonEntity();
    manager->AddComponent<ScoreComponent>();
    manager->AddComponent<red::CameraComponent>(center);
    manager->AddComponent<red::AudioListener>();

    auto* walls = CreateEntity("Walls");

    red::EdgeColliderDesc wallUpColliderDesc;
    wallUpColliderDesc.isTrigger = false;
    wallUpColliderDesc.start = {0.f, 0.f};
    wallUpColliderDesc.end = red::Vector2((float) info.width, 0.f);

    red::EdgeColliderDesc wallDownColliderDesc;
    wallDownColliderDesc.isTrigger = false;
    wallDownColliderDesc.start = {0.f, (float) info.height};
    wallDownColliderDesc.end = {(float) info.width, (float) info.height};

    red::ColliderList* wallColliders = walls->AddComponent<red::ColliderList>();
    wallColliders->AddEdgeCollider(wallUpColliderDesc);
    wallColliders->AddEdgeCollider(wallDownColliderDesc);

    red::PhysicBodyCreationDesc wallBodyDesc = {red::PhysicsBodyType::STATIC_BODY};
    walls->AddComponent<red::PhysicBody>(wallBodyDesc);

    auto* logicSystem = m_world->AddSystem<GameLogicSystem>(paddleOne, paddleTwo, ball);
    logicSystem->m_paddlecollisionSignal = slot;
    m_world->AddSystem<GameControlSystem>(paddleOne, paddleTwo);
}

void PongLevel::Finalize()
{
    m_world->RemoveSystem<GameLogicSystem>();
    m_world->RemoveSystem<GameControlSystem>();
}

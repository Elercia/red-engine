#include "PongLevel.hpp"

#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/Component/CameraComponent.hpp"
#include "RedEngine/Rendering/Component/Sprite.hpp"
#include "RedEngine/Rendering/Component/WindowComponent.hpp"
#include "RedEngine/Rendering/Resource/Texture2D.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"

#include "GameControlSystem.hpp"
#include "GameLogicSystem.hpp"
#include "ScoreComponent.hpp"

void PongLevel::Init()
{
    auto* window = m_world->GetWorldComponent<red::WindowComponent>();

    const red::Vector2 paddleSize = {30.f, 100.f};
    const float ballSize = 30.f;
    const float paddleOffsetFromBorder = 100.f;

    const red::Vector2 arenaSize = {800, 600};
    const red::Vector2 arenaCenter{arenaSize.width / 2.f, arenaSize.height / 2.f};

    const float paddlePosHeight = (arenaSize.height / 2.f) - (paddleSize.y / 2.f);

    red::PhysicBodyCreationDesc ballBodyDesc = {red::PhysicsBodyType::DYNAMIC_BODY};
    red::CircleColliderDesc ballColliderDesc;
    ballColliderDesc.isTrigger = false;
    ballColliderDesc.center = {ballSize / 2.f, ballSize / 2.f};
    ballColliderDesc.radius = ballSize / 2.f;
    ballColliderDesc.restitution = 1.f;

    red::PhysicBodyCreationDesc paddleBodyDesc = {red::PhysicsBodyType::KINEMATIC_BODY};
    red::PolygonColliderDesc paddleColliderDesc;
    paddleColliderDesc.isTrigger = false;
    paddleColliderDesc.points = {{0, 0}, {paddleSize.x, 0}, {paddleSize.x, paddleSize.y}, {0, paddleSize.y}};
    paddleColliderDesc.restitution = 1.f;

    red::SoundDesc ballbounding;
    ballbounding.name = "ball_bouncing";

    red::Entity* ballEntity = nullptr;
    red::Entity* paddleOne = nullptr;
    red::Entity* paddleTwo = nullptr;

    red::PhysicBody* ballPhysicBody = nullptr;

    // Init ball entity
    {
        ballEntity = CreateEntity("Ball");
        ballEntity->AddComponent<red::Sprite>(red::Path::Resource("ball"))->SetRenderLayerIndex(1);
        ballEntity->GetComponent<red::Transform>()->SetLocalPosition(arenaCenter);

        ballPhysicBody = ballEntity->AddComponent<red::PhysicBody>(ballBodyDesc);
        ballPhysicBody->AddCircleCollider(ballColliderDesc);
        ballEntity->AddComponent<red::AudioSource>(ballbounding);
    }

    // setup left paddle
    {
        paddleOne = CreateEntity("PaddleOne");
        paddleOne->AddComponent<red::Sprite>(red::Path::Resource("paddle"))->SetRenderLayerIndex(1);
        paddleOne->GetComponent<red::Transform>()->SetLocalPosition({paddleOffsetFromBorder, paddlePosHeight});

        auto* paddleOneBody = paddleOne->AddComponent<red::PhysicBody>(paddleBodyDesc);
        paddleOneBody->AddPolygonCollider(paddleColliderDesc);
    }

    // Setup right paddle
    {
        paddleTwo = CreateEntity("PaddleTwo");
        paddleTwo->AddComponent<red::Sprite>(red::Path::Resource("paddle"))->SetRenderLayerIndex(1);
        paddleTwo->GetComponent<red::Transform>()->SetLocalPosition(
            red::Vector2(arenaSize.width - paddleOffsetFromBorder - paddleSize.x, paddlePosHeight));

        auto* paddleTwoBody = paddleTwo->AddComponent<red::PhysicBody>(paddleBodyDesc);
        paddleTwoBody->AddPolygonCollider(paddleColliderDesc);
    }

    // Create camera
    {
        auto* manager = CreateEntity("Camera");
        manager->AddComponent<ScoreComponent>();
        manager->AddComponent<red::CameraComponent>(window, red::Vector4(0.f, 0.f, 1.f, 1.f), arenaSize);
        manager->AddComponent<red::AudioListener>();
    }

    // Create walls
    {
        auto* walls = CreateEntity("Walls");

        red::EdgeColliderDesc wallUpColliderDesc;
        wallUpColliderDesc.isTrigger = false;
        wallUpColliderDesc.start = {0.f, 0.f};
        wallUpColliderDesc.end = red::Vector2((float) arenaSize.width, 0.f);

        red::EdgeColliderDesc wallDownColliderDesc;
        wallDownColliderDesc.isTrigger = false;
        wallDownColliderDesc.start = {0.f, (float) arenaSize.height};
        wallDownColliderDesc.end = {(float) arenaSize.width, (float) arenaSize.height};

        red::PhysicBodyCreationDesc wallBodyDesc = {red::PhysicsBodyType::STATIC_BODY};
        auto wallsBody = walls->AddComponent<red::PhysicBody>(wallBodyDesc);

        wallsBody->AddEdgeCollider(wallUpColliderDesc);
        wallsBody->AddEdgeCollider(wallDownColliderDesc);
    }

    // Setup systems
    {
        m_world->AddSystem<GameControlSystem>(paddleOne, paddleTwo);

        auto* logicSystem = m_world->AddSystem<GameLogicSystem>(paddleOne, paddleTwo, ballEntity);
        const auto onCollisionCallback = [](const red::CollisionInfo& collisionInfo)
        { collisionInfo.firstPhysicBody->GetOwner()->GetComponent<red::AudioSource>()->Play(); };
        logicSystem->m_paddlecollisionSignal = ballPhysicBody->m_collisionSignal.Connect(onCollisionCallback);
    }
}

void PongLevel::Finalize()
{
    /*m_world->RemoveSystem<GameLogicSystem>();
    m_world->RemoveSystem<GameControlSystem>();*/
}

RED_COMPONENT_BASIC_FUNCTIONS_IMPL(ScoreComponent)
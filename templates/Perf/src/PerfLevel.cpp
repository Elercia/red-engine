#include "PerfLevel.hpp"

#include "RedEngine/Audio/AudioEvent.hpp"
#include "RedEngine/Audio/Component/AudioListener.hpp"
#include "RedEngine/Audio/Component/AudioSource.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Time/Time.hpp"
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
#include "RedEngine/Utils/Random.hpp"

using namespace red;

namespace perf
{
class CameraManager : public System
{
public:
    CameraManager(red::World* world, Entity* camera) : System(world), m_camera(camera)
    {
    }
    ~CameraManager() override = default;

    void Update() override
    {
        auto* events = m_world->GetWorldComponent<UserInputComponent>();

        Vector2 speed = Vector2(20.f, 20.f) * Time::DeltaTime();
        Vector2 direction;
        if (events->GetKey("Up"))
        {
            direction.y = 1.f;
        }
        else if (events->GetKey("Down"))
        {
            direction.y = -1.f;
        }

        if (events->GetKey("Left"))
        {
            direction.x = -1.f;
        }
        else if (events->GetKey("Right"))
        {
            direction.x = 1.f;
        }

        auto* transform = m_camera->GetComponent<Transform>();

        transform->SetPosition(transform->GetPosition() + (direction * speed));
    }

    Entity* m_camera;
};

void PerfLevel::Init()
{
    Color colors[32];
    for(int i =0; i < 32;i++)
    {
        colors[i] = Color(RandomRange(0, 255), RandomRange(0, 255), RandomRange(0, 255));
    }

    const float worldSizeMin = 0.f;
    const float worldSizeMax = 1000.f;

    m_world->GetPhysicsWorld()->SetGravity({0.f, 100.f});

    // setup walls on the arena
    auto* wallEntity = CreateEntity("Walls");

    red::PhysicBodyCreationDesc wallBodyDesc = {red::PhysicsBodyType::STATIC_BODY};
    auto wallsBody = wallEntity->AddComponent<red::PhysicBody>(wallBodyDesc);

    red::EdgeColliderDesc wallColliderDesc;
    wallColliderDesc.isTrigger = false;
    wallColliderDesc.start = {worldSizeMin, worldSizeMin};
    wallColliderDesc.end = red::Vector2(worldSizeMax, worldSizeMin);
    wallsBody->AddEdgeCollider(wallColliderDesc);

    wallColliderDesc.start = {worldSizeMax, worldSizeMin};
    wallColliderDesc.end = red::Vector2(worldSizeMax, worldSizeMax);
    wallsBody->AddEdgeCollider(wallColliderDesc);

    wallColliderDesc.start = {worldSizeMax, worldSizeMax};
    wallColliderDesc.end = red::Vector2(worldSizeMin, worldSizeMax);
    wallsBody->AddEdgeCollider(wallColliderDesc);

    wallColliderDesc.start = {worldSizeMin, worldSizeMax};
    wallColliderDesc.end = red::Vector2(worldSizeMin, worldSizeMin);
    wallsBody->AddEdgeCollider(wallColliderDesc);

    for (int i = 0; i < 500; i++)
    {
        const Vector2 position = {RandomFloatRange(worldSizeMin, worldSizeMax), RandomFloatRange(worldSizeMin, worldSizeMax)};
        const float scale = RandomFloatRange(0.1f, 1.5f);
        const Vector2 axisscale = {scale, scale};
        const float size = 30.f * scale;
        const int layerIndex = i % 32;

        PhysicBodyCreationDesc bodyDesc = {PhysicsBodyType::DYNAMIC_BODY};
        bodyDesc.linearDamping = worldSizeMax;
        bodyDesc.angularDamping = worldSizeMax;

        CircleColliderDesc colliderDesc;
        colliderDesc.isTrigger = false;
        colliderDesc.center = {size / 2.f, size / 2.f};
        colliderDesc.radius = size / 2.f;
        colliderDesc.restitution = 1.f;

        BindingValue value;
        value.type = BindingType::Vector4;
        auto vec4Color = colors[i % 32].AsVector4();
        memcpy(value.floats, &vec4Color.x, sizeof(value.floats));

        auto* ball = CreateEntity("Ball_" + i);
        auto* s = ball->AddComponent<Sprite>(Path::Resource("ball"));
        s->SetRenderLayerIndex(layerIndex);
        s->GetMaterial().overiddenBindings.bindings[BindingIndex::Color] = value;

        ball->GetComponent<Transform>()->SetPosition(position);
        ball->GetComponent<Transform>()->SetScale(axisscale);
        auto ballBody = ball->AddComponent<PhysicBody>(bodyDesc);
        ballBody->AddCircleCollider(colliderDesc);

        //ballBody->ApplyForce({10.f, 10.f}, {size / 2.f, size / 2.f});
    }

    auto* window = m_world->GetWorldComponent<red::WindowComponent>();

    auto* manager = CreateEntity("Manager");
    manager->AddComponent<red::CameraComponent>(window, red::Vector4(0.f, 0.f, 1.f, 1.f), red::Vector2i{1000, 1000});

    m_world->AddSystem<CameraManager>(manager);
}

void PerfLevel::Finalize()
{
}
}  // namespace perf
